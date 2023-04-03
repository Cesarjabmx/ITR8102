using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace PRACTICA_ARDUINO_ITR8102
{
    public partial class FrmPuertas : Form
    {
        string datoSerial = "";
        Graphics papel;
        Bitmap bmp1 = new Bitmap(@"C:\Users\Cesar\Documents\SistemasPro\puertas-abiertas.jpg");
        Bitmap bmp2 = new Bitmap(@"C:\Users\Cesar\Documents\SistemasPro\puertas-cerradas.jpg");

        public FrmPuertas()
        {
            InitializeComponent();
            papel = picbPuertaAbierta.CreateGraphics();
            papel.DrawImage(bmp2, 0, 0, bmp2.Width, bmp2.Height);
            string[] puertos = SerialPort.GetPortNames();
            foreach (string item in puertos)
            {
                cmbPuertos.Items.Add(item);
            }
        }

        private void chkAbrir_CheckedChanged(object sender, EventArgs e)
        {
            if (chkAbrir.Checked)
            {
                try
                {
                    if (!prtSerial.IsOpen)
                    {
                        prtSerial.Open();
                        chkAbrir.Text = "Puerto COM Abierto";
                    }
                }
                catch (Exception error)
                {

                    MessageBox.Show(error.ToString());
                    chkAbrir.Checked = false;
                }
            }
            else
            {
                try
                {
                    if (prtSerial.IsOpen)
                    {
                        prtSerial.Close();
                        chkAbrir.Text = "Puerto COM Cerrado";
                    }
                }
                catch (Exception error)
                {

                    MessageBox.Show(error.ToString());
                    //chkAbrir.Checked = false;
                }
            }
        }

        private void prtSerial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                prtSerial.ReadTimeout = 100;
                datoSerial = prtSerial.ReadTo("\r\n");
                Invoke(new EventHandler(RecibirTexto));
            }
            catch (Exception error)
            {
                MessageBox.Show(error.ToString());
                prtSerial.DiscardInBuffer();
            }
        }

        private void cmbPuertos_SelectedIndexChanged(object sender, EventArgs e)
        {
            prtSerial.PortName = cmbPuertos.SelectedItem.ToString();
            MessageBox.Show("Puerto " + prtSerial.PortName + " seleccionado.");
        }

        private void RecibirTexto(Object sender, EventArgs e)
        {
            txtSerial.Clear();
            txtSerial.AppendText(datoSerial);
            AnalizarCadena(datoSerial);
        }

        private void AnalizarCadena(string cadena)
        {
            char[] separador = { ':' };
            string[] trama = cadena.Split(separador);
            foreach  (string item in trama)
            {
                item.Trim();
            }
            if(trama.Length > 1)
            {
                if (trama[trama.Length - 1] == "abierto")
                    papel.DrawImage(bmp1, 0, 0, bmp1.Width, bmp1.Height);
                if (trama[trama.Length - 1] == "cerrado")
                    papel.DrawImage(bmp2, 0, 0, bmp2.Width, bmp2.Height);
            }
        }
    }
}
