using System;

using UIKit;

namespace First_iOSapp
{
    public partial class ViewController : UIViewController
    {

        partial void UIButton198_TouchUpInside(UIButton sender)
        {

            Random rnd = new System.Random();    // インスタンスを生成
            int x = rnd.Next(7); //Generate rnd 0-10
            /* 
            乱数表示確認をしたい時用 string rnd_num = x.ToString();
            label00.Text = rnd_num;
            */
            if (x % 2 == 0)
            {
                label00.Text = "吉";
            }
            else
            {
                label00.Text = "凶";
            }
            if (x % 7 == 0)
            {
                label00.Text = "大吉";
            }
            labelcount.Text = "はじめてのiOSアプリ Visual Studio 2017 簡易おみくじ";

        }

        protected ViewController(IntPtr handle) : base(handle)
        {
            // Note: this .ctor should not contain any initialization logic.
        }

        public override void ViewDidLoad()
        {
            base.ViewDidLoad();
            // Perform any additional setup after loading the view, typically from a nib.
        }

        public override void DidReceiveMemoryWarning()
        {
            base.DidReceiveMemoryWarning();
            // Release any cached data, images, etc that aren't in use.
        }
    }
}
