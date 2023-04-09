using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public class My_Button : Control
    {
        #region
        private StringFormat SF = new StringFormat();
        private bool MouseIsEnter = false;
        private bool MouseIsPress = false;
        private bool roundingEnable = false;
        Animation CurtainButtonAnim = new Animation();
        Animation TextSlideAnim = new Animation();
        Dictionary<Animation, Rectangle> RippleButtonAnimDic = new Dictionary<Animation, Rectangle>();
        Point ClickLocation = new Point();

        #endregion










        public Color BorderColor { get; set; } = Color.Tomato; //Цвет обводки (границы) кнопки

        public bool BorderColorEnabled { get; set; } = false; // Указывает, включено ли использование отдельного цвета обводки (границы) кнопки

        public Color BorderColorOnHover { get; set; } = Color.Tomato; // Цвет обводки (границы) кнопки при наведении курсора
        public bool BorderColorOnHoverEnabled { get; set; } = false; //Указывает, включено ли использование отдельного цвета обводки (границы) кнопки при наведении курсора
        public bool BackColorGradientEnabled { get; set; } = false;//Указывает, включен ли градинт кнопки
        public Color BackColorAdditional { get; set; } = Color.Gray;//Дополнительный фоновый цвет кнопки используемый для создания градиента (При BackColorGradientEnabled = true)
        public LinearGradientMode BackColorGradientMode { get; set; } = LinearGradientMode.Horizontal; //Определяет направление линейного градиента шапки
        public string TextHover { get; set; } // Текст, отображаемый при наведении курсора


        public bool RoundingEnable // Вкд / вкл закругление обьекта
        {
            get => roundingEnable;
            set
            {
                roundingEnable = value;
                Refresh();
            }
        }

        private int roundingPercent = 100;
        [DisplayName("Rounding [%]")]
        [DefaultValue(100)]
        public int Rounding
        {
            get => roundingPercent;
            set
            {
                if (value >= 0 && value <= 100)
                {
                    roundingPercent = value;

                    Refresh();
                }
            }
        }
        public bool UseRippleEffect { get; set; } = true; //  Вкл/Выкл эффект волны по нажатию кнопки курсором.
        public Color RippleColor { get; set; } = Color.Yellow; //Цвет эффекта волны по нажатию кнопки курсором
        public bool UseDownPressEffectOnClick { get; set; }// Вкл/Выкл эффект нажатия кнопки










        public My_Button()
        {
            SetStyle(
                 ControlStyles.AllPaintingInWmPaint |
                 // Если присвоено значение true, элемент управления не обрабатывает сообщение окна WM_ERASEBKGND, чтобы снизить мерцание. Этот стиль следует применять, только если бит UserPaint имеет значение true.
                 ControlStyles.OptimizedDoubleBuffer |
                 // Если присвоено значение true, элемент управления сначала прорисовывается в буфер, а не сразу на экран, что позволяет снизить мерцание. Если для этого стиля задано значение true, следует также установить true для стиля AllPaintingInWmPaint.
                 ControlStyles.ResizeRedraw |
                 // Если присвоено значение true, элемент управления перерисовывается при изменении его размера.
                 ControlStyles.SupportsTransparentBackColor |
                 // Если присвоено значение true, элемент управления принимает параметр BackColor c альфа-составляющей, при значении которой менее 255 имитируется прозрачность. Прозрачность имитируется, только если биту UserPaint присвоено значение true, а родительский элемент управления наследуется от класса Control.
                 ControlStyles.UserPaint |
                 // Если присвоено значение true, отображение элемента управления выполняет сам элемент, а не операционная система. Если присвоено значение false, событие Paint не возникает. Этот стиль применяется только к классам, производным от Control.
                 ControlStyles.Opaque |
                 // Если присвоено значение true, элемент управления отображается непрозрачным, а фон не закрашивается.
                 ControlStyles.Selectable |
                 // Если присвоено значение true, элемент управления может получать фокус.
                 ControlStyles.UserMouse |
                 // Если присвоено значение true, элемент управления самостоятельно выполняет обработку событий мыши, и эти события не обрабатываются операционной системой.
                 ControlStyles.EnableNotifyMessage,
                 // Если присвоено значение true, метод OnNotifyMessage(Message) вызывается для каждого сообщения, которое отправляется в метод WndProc(Message) этого элемента управления. По умолчанию этот стиль имеет значение false. Стиль EnableNotifyMessage не работает в режиме частичного доверия.
                 true);
            DoubleBuffered = true; // двойная буфирезация при прорисовке обьекта

            Size = new Size(100, 30); // начальный размер блока управления

            Font = new Font("Verdana", 8.25F, FontStyle.Regular); // начальные свойства шрифта
            Cursor = Cursors.Hand;
            BackColor = Color.Tomato;
            ForeColor = Color.White;

           SF.Alignment = StringAlignment.Center; //выравнивания по гор и вер
           SF.LineAlignment = StringAlignment.Center;
        }
















      
            protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e); // базовый метод , нужен для вызова обработчиков событий
            // Graphics отвечает за визуализацию црафического интерфейса
            Graphics graph = e.Graphics;
            
            graph.SmoothingMode = SmoothingMode.HighQuality;// качество визуализации 
            graph.InterpolationMode = InterpolationMode.HighQualityBicubic;
            graph.PixelOffsetMode = PixelOffsetMode.HighQuality;
            graph.SmoothingMode = SmoothingMode.AntiAlias; 
            graph.Clear(Parent.BackColor);// очищает поверхность рисования и заливает его нужным цветом 





            Rectangle rec = new Rectangle(0, 0, Width - 1, Height - 1); // коор  коор размер размер
           
            // закругленный прямуг
            Rectangle recStroke = new Rectangle(0, 0, (int)CurtainButtonAnim.Value, Height - 1);

            
            Rectangle rectText = new Rectangle((int)TextSlideAnim.Value, rec.Y, rec.Width, rec.Height);
            Rectangle rectTextHover = new Rectangle((int)TextSlideAnim.Value - rec.Width, rec.Y, rec.Width, rec.Height);
            



            

            float roundingValue = 0.1F;
            if (RoundingEnable && roundingPercent > 0)
            {
                roundingValue = Height / 100F * roundingPercent;
            }
            GraphicsPath rectPath = Drawer.RoundedRect(rec, roundingValue);
            Region = new Region(rectPath);
            graph.Clear(Parent.BackColor);



            Brush headerBrush = new SolidBrush(BackColor);
            if (BackColorGradientEnabled)
            {
                if (rec.Width > 0 && rec.Height > 0)
                    headerBrush = new LinearGradientBrush(rec, BackColor, BackColorAdditional, BackColorGradientMode);
            }

            Brush borderBrush = headerBrush;
            if (BorderColorEnabled)
            {
                borderBrush = new SolidBrush(BorderColor);

                if (MouseIsEnter && BorderColorOnHoverEnabled)
                    borderBrush = new SolidBrush(BorderColorOnHover);
            }

            // Основной прямоугольник (Фон)
            graph.DrawPath(new Pen(BackColor), rectPath);
            graph.FillPath(new SolidBrush(BackColor), rectPath);
            graph.DrawString(Text, Font, new SolidBrush(ForeColor), rec, SF);
            
            graph.SetClip(rectPath);

            // Рисуем доп. прямоугольник (Наша шторка)
            graph.DrawRectangle(new Pen(Color.FromArgb(60, Color.White)), recStroke);
            graph.FillRectangle(new SolidBrush(Color.FromArgb(60, Color.White)), recStroke);

            
            //            -------

            if (UseRippleEffect == false)
            {
                // Стандартное рисование праямоугольника при клике
                if (MouseIsPress)
                {
                    graph.DrawRectangle(new Pen(Color.FromArgb(30, Color.Green)), rec);// цвет
                    graph.FillRectangle(new SolidBrush(Color.FromArgb(60, Color.Yellow)), rec); // заливка прямоугольника
                    graph.DrawString(Text, Font, new SolidBrush(Color.Blue), rec, SF);
                }
            }
            else
            {
                // Ripple Effect - Волна
                for (int i = 0; i < RippleButtonAnimDic.Count; i++)
                {
                    KeyValuePair<Animation, Rectangle> animRect = RippleButtonAnimDic.ToList()[i];
                    Animation MultiRippleButtonAnim = animRect.Key;
                    Rectangle rectMultiRipple = animRect.Value;

                    rectMultiRipple = new Rectangle(
                       ClickLocation.X - (int)MultiRippleButtonAnim.Value / 2,
                       ClickLocation.Y - (int)MultiRippleButtonAnim.Value / 2,
                       (int)MultiRippleButtonAnim.Value,
                       (int)MultiRippleButtonAnim.Value
                       );

                    if (MultiRippleButtonAnim.Value > 0 && MultiRippleButtonAnim.Value < MultiRippleButtonAnim.TargetValue)
                    {
                        graph.DrawEllipse(new Pen(Color.FromArgb(30, RippleColor)), rectMultiRipple);
                        graph.FillEllipse(new SolidBrush(Color.FromArgb(30, RippleColor)), rectMultiRipple);
                    }
                    else if (MultiRippleButtonAnim.Value == MultiRippleButtonAnim.TargetValue)
                    {
                        if (MouseIsPress == false)
                        {
                            MultiRippleButtonAnim.Value = 0;
                            MultiRippleButtonAnim.Status = Animation.AnimationStatus.Completed;
                        }
                        else
                        {
                            if (i == RippleButtonAnimDic.Count - 1)
                            {
                                graph.DrawEllipse(new Pen(Color.FromArgb(30, RippleColor)), rectMultiRipple);
                                graph.FillEllipse(new SolidBrush(Color.FromArgb(30, RippleColor)), rectMultiRipple);
                            }
                        }
                    }
                }
                // Удаляем из очереди выполненные анимации волны
                List<Animation> completedRippleAnimations = RippleButtonAnimDic.Keys.ToList().FindAll(x => x.Status == Animation.AnimationStatus.Completed);
                for (int i = 0; i < completedRippleAnimations.Count; i++)
                    RippleButtonAnimDic.Remove(completedRippleAnimations[i]);
            }


            //      -------
            
            
            if (MouseIsEnter)
            {
                graph.DrawRectangle(new Pen(Color.FromArgb(60, Color.White)), rec);// цвет
                graph.FillRectangle(new SolidBrush(Color.FromArgb(60, Color.White)), rec); // заливка прямоугольника

            }
            
        }
            
        protected override void OnMouseEnter(EventArgs e) // курсор заходит в видимую область 
        {
            base.OnMouseEnter(e);
            MouseIsEnter = true;
            Invalidate(); // перерисовка кнопки с учетом изменненных параметров
        }
        protected override void OnMouseLeave(EventArgs e) // выходит, замечательно выходит =)
        {
            base.OnMouseLeave(e);
            MouseIsEnter = false;
            Invalidate();
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);
            MouseIsPress = false;
            Invalidate();
        }
        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            MouseIsPress = true;

            ClickLocation = e.Location;
            Invalidate();
        }

    }
    
}
