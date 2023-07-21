namespace SpritesToAtlas
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            SelectSprites = new Button();
            AtlasView = new PictureBox();
            AtlasPanel = new Panel();
            ButtonExport = new Button();
            ((System.ComponentModel.ISupportInitialize)AtlasView).BeginInit();
            AtlasPanel.SuspendLayout();
            SuspendLayout();
            // 
            // SelectSprites
            // 
            SelectSprites.BackColor = SystemColors.ActiveCaption;
            SelectSprites.Location = new Point(731, 12);
            SelectSprites.Name = "SelectSprites";
            SelectSprites.Size = new Size(104, 42);
            SelectSprites.TabIndex = 0;
            SelectSprites.Text = "SelectSprites";
            SelectSprites.UseVisualStyleBackColor = false;
            SelectSprites.Click += button1_Click;
            // 
            // AtlasView
            // 
            AtlasView.BackColor = SystemColors.AppWorkspace;
            AtlasView.Cursor = Cursors.Cross;
            AtlasView.Location = new Point(7, 6);
            AtlasView.Name = "AtlasView";
            AtlasView.Size = new Size(700, 400);
            AtlasView.TabIndex = 1;
            AtlasView.TabStop = false;
            // 
            // AtlasPanel
            // 
            AtlasPanel.AutoScroll = true;
            AtlasPanel.BackColor = SystemColors.ActiveCaption;
            AtlasPanel.Controls.Add(AtlasView);
            AtlasPanel.Location = new Point(12, 12);
            AtlasPanel.Name = "AtlasPanel";
            AtlasPanel.Size = new Size(713, 790);
            AtlasPanel.TabIndex = 2;
            // 
            // ButtonExport
            // 
            ButtonExport.Location = new Point(731, 60);
            ButtonExport.Name = "ButtonExport";
            ButtonExport.Size = new Size(104, 41);
            ButtonExport.TabIndex = 3;
            ButtonExport.Text = "Export";
            ButtonExport.UseVisualStyleBackColor = true;
            ButtonExport.Click += ButtonExport_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(839, 814);
            Controls.Add(ButtonExport);
            Controls.Add(AtlasPanel);
            Controls.Add(SelectSprites);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)AtlasView).EndInit();
            AtlasPanel.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private Button SelectSprites;
        private PictureBox AtlasView;
        private Panel AtlasPanel;
        private Button ButtonExport;
    }
}