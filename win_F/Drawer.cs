
using System.Drawing;
using System.Drawing.Drawing2D;
namespace WinFormsApp1
{
    public static class Drawer
    {
        public static GraphicsPath RoundedRect(Rectangle rec, float RoundSize) {

            GraphicsPath gp = new GraphicsPath();

            gp.AddArc(rec.X, rec.Y, RoundSize, RoundSize, 180, 90);//Присоединяет дугу эллипса к текущей фигуре.
            gp.AddArc(rec.X + rec.Width - RoundSize, rec.Y, RoundSize, RoundSize, 270, 90);
            gp.AddArc(rec.X + rec.Width - RoundSize, rec.Y + rec.Height - RoundSize, RoundSize, RoundSize, 0, 90);
            gp.AddArc(rec.X, rec.Y + rec.Height - RoundSize, RoundSize, RoundSize, 90, 90);

            gp.CloseFigure();
            return gp;
        }

    }
}
