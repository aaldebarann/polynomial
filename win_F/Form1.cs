using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {

        [DllImport("Dll1.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]

        public static extern void MainString(StringBuilder val);
        public Form1()
        {
            InitializeComponent();
        }
        string txt;
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            txt = textBox1.Text;

        }



        private void Button_Click(object sender, EventArgs e)
        {
            StringBuilder val = new StringBuilder(txt);
            MainString(val);
            textBox1.ForeColor = Color.Black;
            textBox1.Text = val.ToString();
        }

        private void textBox1_MouseClick(object sender, MouseEventArgs e)
        {
            textBox1.ForeColor = Color.Black;
            textBox1.Text = "";
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
