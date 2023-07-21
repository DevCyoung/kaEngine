using System.Drawing.Imaging;

namespace SpritesToAtlas
{
    public partial class Form1 : Form
    {
        public Point cursurPos;
        public Size pad;
        public Size leftTopMargin;

        public Font font;
        public Bitmap atlasImage;

        OpenFileDialog odf;
        SaveFileDialog sdf;

        public Form1()
        {
            InitializeComponent();

            AtlasView.SizeMode = PictureBoxSizeMode.AutoSize;

            leftTopMargin = new Size(5, 5);
            cursurPos = new Point(leftTopMargin.Width, leftTopMargin.Height);
            pad = new Size(10, 20);
            atlasImage = new Bitmap(AtlasView.Width, AtlasView.Height);

            font = new Font("Arial", 10);

            odf = new OpenFileDialog();
            odf.Filter = "Image Files (*.png, *.jpg, *.bmp)|*.png;*.jpg;*.bmp";
            odf.Multiselect = true;

            sdf = new SaveFileDialog();
            sdf.Filter = "Image Files (*.png, *.jpg, *.bmp)|*.png;*.jpg;*.bmp";
        }

        private void lineFead()
        {
            cursurPos.Y += pad.Height;
        }

        private void carriageReturn()
        {
            cursurPos.X = leftTopMargin.Width;
        }

        private void moveCursurX(int width)
        {
            cursurPos.X += width;
        }
        private void moveCursurY(int height)
        {
            cursurPos.Y += height;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Graphics atalsGraphics = Graphics.FromImage(atlasImage);

            if (DialogResult.OK == odf.ShowDialog())
            {
                string[] files = odf.FileNames;

                if (files.Length == 0)
                {
                    return;
                }

                //Load Image
                Bitmap[] sprties = new Bitmap[files.Length];

                for (int i = 0; i < files.Length; i++)
                {
                    sprties[i] = new Bitmap(files[i]);
                }

                int maxSpriteHeight = 0;

                for (int i = 0; i < files.Length; i++)
                {
                    if (sprties[i].Height > maxSpriteHeight)
                    {
                        maxSpriteHeight = sprties[i].Height;
                    }
                }



                atalsGraphics.DrawString(odf.SafeFileNames[0],
                    font, Brushes.Yellow, cursurPos.X, cursurPos.Y);

                moveCursurY(font.Height);
                carriageReturn();
                lineFead();



                //Draw Bmp
                for (int i = 0; i < files.Length; i++)
                {

                    if (cursurPos.X + sprties[i].Width >= atlasImage.Width + pad.Width)
                    {
                        carriageReturn();
                        moveCursurY(maxSpriteHeight);
                        lineFead();
                    }

                    if (atlasImage.Height < cursurPos.Y + pad.Height + maxSpriteHeight)
                    {
                        Bitmap newBitmp = new Bitmap(atlasImage.Width, atlasImage.Height + 400);
                        Graphics newGraphics = Graphics.FromImage(newBitmp);

                        newGraphics.DrawImage(atlasImage, 0, 0);

                        atlasImage = newBitmp;
                        atalsGraphics = newGraphics;
                    }


                    atalsGraphics.DrawImage(sprties[i], cursurPos.X, cursurPos.Y);


                    //Update x,y
                    moveCursurX(sprties[i].Width + pad.Width);
                }

                carriageReturn();
                moveCursurY(maxSpriteHeight);
                lineFead();

                AtlasView.Image = atlasImage;

            }
        }

        private void ButtonExport_Click(object sender, EventArgs e)
        {
            sdf.ShowDialog();

            if (sdf.FileName != "")
            {
                atlasImage.Save(sdf.FileName, ImageFormat.Png);
                //atlasImage.Save(sdf.FileName, ImageFormat.Png);
            }
            else
            {
                MessageBox.Show("Please enter a file name.");
            }
        }
    }
}