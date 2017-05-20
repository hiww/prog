PImage img;
PImage text;
PImage face1;
PImage check1;
void setup() {
	size( 1212, 718 );//campussize=1212x683
	PFont font = createFont("MS Gothic",48,true);
	textFont (font);
	img = loadImage("data/wall.jpg");
	text = loadImage("data/output.jpg");
	face1 = loadImage("data/good.jpg");
	check1 = loadImage("data/check.png");
	fill( 0, 0, 0 );
	textSize( 20 );
	image(img, 0, 0);
}
int total = 11, tmp, r, rt, cnt = 0, judge, judget, flag, check, checkt, i, j,a,b,  x1, y1,a1, b1, num = -1; 
void mousePressed() {
	num = (int)random(0,30);
	if (cnt == total) cnt = 0;
	if (cnt == 0) {
		image(img, 0, 0);
		a = (int)random(1,7);
		b = (int)random(1,4);
		i = (int)random(1,7);
		j = (int)random(1,4);
		x1 = 163*(i-1);
		y1 = 170*(j-1);
		a1 = 163*(a-1);
		b1 = 170*(b-1);
	} 
	while (cnt == total) {
		a = (int)random(1,7);
		b = (int)random(1,4);
		i = (int)random(1,7);
		j = (int)random(1,4);
		x1 = 163*(i-1);
		y1 = 170*(j-1);
		a1 = 163*(a-1);
		b1 = 170*(b-1);
	}
	cnt++;
}

void mouseClicked() {
	image(text, 0, 683);
	tmp = total - cnt;
	text("次のおみくじ移動まであと" + tmp + "回", 900, 710);
	image(check1, mouseX, mouseY);
	for (;175*(a-1) <= mouseX ;) {
		for (;mouseX   <= 175*a;) {
			for (;170*(b-1) <= mouseY;) {
				for (;mouseY <= 170*b;) {
					checkt = 1;  
					break;
				}
				break;
			}
			break;
		}
		break;
	}
	if (checkt != 1) {
		rt = abs(mouseX*mouseX + mouseY*mouseY - a1*a1 + b1*b1);
		if (sqrt(rt) <= 500) {
			println("近いよ！！");
			text("近いよ！！", 480, 710);
		} else if (sqrt(rt) >= 900) {
			println("とっても遠いよ！！");
			fill( 0, 0, 0 );
			textSize( 20 );
			text("とっても遠いよ！！", 480, 710);
		} else {
			println("ちょっと遠いかな？");
			fill( 0, 0, 0 );
			textSize( 20 );
			text("ちょっと遠いかな？", 480, 710);
		}
	}
	if (checkt == 1) {
		if (judget == 0) {
			println("大吉を手に入れた！");
			image(face1, 480, 690);
			text("大吉を引いたよ、もう一度最初から！",  500, 710);
			cnt = 0;
		}
		if (judget == 1) {
			println("大吉を手に入れた！");
			image(face1, 480, 690);
			text("大吉を引いたよ、もう一度最初から！",  500, 710);
			cnt = 0;
		}  
		if (judget == 2) {
			println("凶を手に入れた！");
			text("凶を引いたね、まだまだこれから！",  580, 710); 
		}  
		if (judget == 3) {
			println("吉を手に入れた！");
			text("吉を引いたよ、まだまだ頑張ろう！",  580, 710);
		}
		checkt = 0;
	}
	for (;175*(i-1) <= mouseX ;) {
		for (;mouseX   <= 175*i;) {
			for (;170*(j-1) <= mouseY;) {
				for (;mouseY <= 170*j;) {
					check = 1;  
					break;
				}
				break;
			}
			break;
		}
		break;
	}

	switch( num % 4 ) {
		case 0:
			judge = 0;
			//text( "大凶", 70 + x1, 108 + y1);    
			//text( "大吉", 70 + a1, 108 + b1);    
			break;
		case 1:
			judge = 1;  
			//text( "大凶", 70 + x1, 108 + y1);    
			//text( "大吉", 70 + a1, 108 + b1);    
			break;
		case 2:
			judge = 2;
			//text( "凶",70 + x1, 108 + y1);
			//text( "凶",70 + a1, 108 + b1);
			break;
		case 3:
			judge = 3;
			//text( "吉", 70 + x1, 108 + y1);
			//text( "吉", 70 + a1, 108 + b1);
			break;
	}
	if (check != 1) {
		r = abs(mouseX*mouseX + mouseY*mouseY - x1*x1 + y1*y1);
		if (sqrt(r) <= 500) {
			println("近いよ！！");
			text("近いよ！！", 20, 710);
		} else if (sqrt(r) >= 900) {
			println("とっても遠いよ！！");
			fill( 0, 0, 0 );
			textSize( 20 );
			text("とっても遠いよ！！", 20, 710);
		} else {
			println("ちょっと遠いかな？");
			fill( 0, 0, 0 );
			textSize( 20 );
			text("ちょっと遠いかな？", 20, 710);
		}
	}
	if (check == 1) {
		if (judge == 0) {
			println("大凶を手に入れた！");
			text("大凶を引いちゃった... やりなおし。",  20, 710);
      cnt = 0;
    }  
		if (judge == 1) {
			println("大凶を手に入れた！");
			text("大凶を引いちゃった... やりなおし。",  20, 710);
      cnt = 0;
		}  
		if (judge == 2) {
			println("凶を手に入れた！");
			text("凶を引いたね、まだまだこれから！",  20, 710); 
		}  
		if (judge == 3) {
			println("吉を手に入れた！");
			text("吉を引いたよ、まだまだ頑張ろう！",  20, 710);
		}
	}  
	check = 0;
}
void draw() {

}