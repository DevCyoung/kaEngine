using System.Collections;
using System.Drawing.Imaging;
using System.IO;


namespace SpritesToAtlas
{
    public partial class Form1 : Form
    {

        public Point mCursurPos;
        public Size mPad;
        public Size mLeftTopMargin;

        public Font mFont;
        public Bitmap mAtlasImage;

        FolderBrowserDialog mFBD;
        SaveFileDialog mSFD;

        Stack<Point> mPrevPosStack;

        Pen mMagentaPen;

        public Form1()
        {
            InitializeComponent();



            AtlasView.SizeMode = PictureBoxSizeMode.AutoSize;

            mLeftTopMargin = new Size(5, 5);
            mCursurPos = new Point(mLeftTopMargin.Width, mLeftTopMargin.Height);
            mPad = new Size(10, 10);
            mAtlasImage = new Bitmap(AtlasView.Width, AtlasView.Height);
            mFont = new Font("Arial", 12);
            mFBD = new FolderBrowserDialog();            
            mSFD = new SaveFileDialog();
            mSFD.Filter = "Image Files (*.png, *.jpg, *.bmp)|*.png;*.jpg;*.bmp";
            mPrevPosStack = new Stack<Point>();
            mMagentaPen = new Pen(Brushes.Magenta);
        }

        private void LF()
        {
            mCursurPos.Y += mPad.Height;
        }

        private void CR()
        {
            mCursurPos.X = mLeftTopMargin.Width;
        }

        private void MoveAddCursurX(int width)
        {
            mCursurPos.X += width;
        }
        private void MoveAddCursurY(int height)
        {
            mCursurPos.Y += height;
        }

        private void DrawSprite(string spritesName, string[] filePaths)
        {
            Graphics atalsGraphics = Graphics.FromImage(mAtlasImage);
            mPrevPosStack.Push(mCursurPos);

            //Load Image
            Bitmap[] sprties = new Bitmap[filePaths.Length];

            for (int i = 0; i < filePaths.Length; i++)
            {
                sprties[i] = new Bitmap(filePaths[i]);
            }

            Size SpriteSize = new Size(sprties[0].Width, sprties[0].Height);
                                  
            Point captionLT = new Point(mCursurPos.X, mCursurPos.Y);


            string caption = $"{spritesName}  " +
                $"LT: {mCursurPos.X}, {mCursurPos.Y + mFont.Height + mPad.Height},  " +
                $"BackSize: {SpriteSize.Width}, {SpriteSize.Height}  " +
                $"Pad: {mPad.Width} {mPad.Height} Cnt: {filePaths.Length}";
            MoveAddCursurY(mFont.Height);
            LF();
            CR();

            //Draw Bmp
            for (int i = 0; i < filePaths.Length; i++)
            {
                //next Line
                if (mAtlasImage.Width < mCursurPos.X + SpriteSize.Width + mPad.Width)
                {
                    MoveAddCursurY(SpriteSize.Height);
                    LF();
                    CR();
                }

                //Expand Image
                if (mAtlasImage.Height < mCursurPos.Y + SpriteSize.Height + mPad.Height)
                {
                    Bitmap newBitmp = new Bitmap(mAtlasImage.Width, mAtlasImage.Height + 400);
                    Graphics newGraphics = Graphics.FromImage(newBitmp);

                    newGraphics.DrawImage(mAtlasImage, 0, 0);

                    mAtlasImage = newBitmp;
                    atalsGraphics = newGraphics;
                }

                atalsGraphics.DrawRectangle(mMagentaPen, mCursurPos.X - 1, mCursurPos.Y - 1, sprties[i].Width + 1, sprties[i].Height + 1);
                atalsGraphics.DrawImage(sprties[i], mCursurPos.X, mCursurPos.Y);
                
                MoveAddCursurX(sprties[i].Width + mPad.Width);
            }

            atalsGraphics.DrawString(caption,
                mFont, Brushes.Yellow, captionLT.X, captionLT.Y);

            MoveAddCursurY(SpriteSize.Height);
            LF();
            CR();


            AtlasView.Image = mAtlasImage;
        }

        private void button1_Click(object sender, EventArgs e)
        {            
            if (DialogResult.OK != mFBD.ShowDialog())
            {
                return;
            }

            string[] directoryPaths = Directory.GetDirectories(mFBD.SelectedPath);            

            foreach (string path in directoryPaths)
            {
                string[] Dirfilepaths = Directory.GetFiles(path);                

                if (Dirfilepaths.Length == 0)
                {
                    continue;
                }

                Array.Sort(Dirfilepaths,
                    (a, b) => a.Length - b.Length == 0 ? a.CompareTo(b) : a.Length - b.Length
                    );


                DrawSprite(Path.GetFileNameWithoutExtension(path), Dirfilepaths);
            }

            string[] filePaths = Directory.GetFiles(mFBD.SelectedPath);            

            foreach (string path in filePaths)
            {
                string[] files = { path };

                if (files.Length == 0)
                {
                    continue;
                }

                DrawSprite(Path.GetFileNameWithoutExtension(path), files);
            }
        }

            private void ButtonExport_Click(object sender, EventArgs e)
            {
                if (mPrevPosStack.Count <= 0)
                {
                    MessageBox.Show("Empty Sprites");
                    return;
                }

                mSFD.ShowDialog();

                if (mSFD.FileName != "")
                {
                    Bitmap copyBitmap = new Bitmap(mAtlasImage.Width, mCursurPos.Y);
                    Graphics copyGraphics = Graphics.FromImage(copyBitmap);

                    Rectangle rect = new Rectangle(0, 0, mAtlasImage.Width, mCursurPos.Y);
                    copyGraphics.DrawImageUnscaledAndClipped(mAtlasImage, rect);

                    copyBitmap.Save(mSFD.FileName, ImageFormat.Png);
                }
                else
                {
                    MessageBox.Show("Please enter a file name.");
                }
            }

            private void PrevAtlasButton_Click(object sender, EventArgs e)
            {
                if (mPrevPosStack.Count <= 0)
                {
                    MessageBox.Show("Empty Sprites");

                    return;
                }

                Point prevPos = mPrevPosStack.Pop();

                Bitmap copyBitmap = new Bitmap(mAtlasImage.Width, mAtlasImage.Height);
                Graphics copyGraphics = Graphics.FromImage(copyBitmap);

                Rectangle rect = new Rectangle(0, 0, mAtlasImage.Width, prevPos.Y);

                copyGraphics.DrawImageUnscaledAndClipped(mAtlasImage, rect);

                mAtlasImage = copyBitmap;
                AtlasView.Image = mAtlasImage;
                mCursurPos = prevPos;
            }
        }
    }