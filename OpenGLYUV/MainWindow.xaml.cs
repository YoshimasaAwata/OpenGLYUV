using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace OpenGLYUV
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            _playTimer = new DispatcherTimer();
            _playTimer.Tick += new EventHandler(CompositionTarget_Rendering);
            _playTimer.Interval = new TimeSpan(0, 0, 0, 0, 33);
        }

        [System.Runtime.InteropServices.DllImport("../ShowYUV.dll")]
        private static extern int CreateOpenGLWindow(string fileName);

        [System.Runtime.InteropServices.DllImport("../ShowYUV.dll")]
        private static extern int Render();

        void CompositionTarget_Rendering(object? sender, EventArgs e)
        {
            int rc = Render();
            if (rc != 0)
            {
                _playTimer.Stop();
            }
        }

        private void FileOpen_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.Title = "YUVファイルの選択";
            dialog.Filter = "YUVァイル (*.yuv)|*.yuv";
            dialog.CheckFileExists = true;

            // ダイアログを表示する
            if (dialog.ShowDialog() == true)
            {
                FileName.Text = dialog.FileName;
                Play.IsEnabled = true;
                CreateOpenGLWindow(dialog.FileName);
            }

        }

        DispatcherTimer _playTimer;
        private void Play_Click(object sender, RoutedEventArgs e)
        {
            Play.IsEnabled = false;
            _playTimer.Start();
        }
    }
}
