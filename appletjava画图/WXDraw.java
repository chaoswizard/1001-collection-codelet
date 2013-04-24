import java.applet.Applet;
import java.awt.*;


public class WXDraw extends Applet
{
	private int x1,y1;
	private int x2,y2;
	private boolean downmouse;
	private boolean upmouse;
	private boolean firstdone;
	public void init()
	{
	
	downmouse=false;
	upmouse=false;
	firstdone=false;
	setBackground(new Color(170,180,220));
	}
	public boolean mouseDown(Event e,int x,int y)
	{
		x1=x;
		y1=y;
		firstdone=true;
		downmouse=true;	
		repaint();
		return true;
	}
	public boolean mouseUp(Event e,int x,int y)
	{
		x2=x1;y2=y1;
		x1=x;y1=y;
		upmouse=true;
		repaint();
        return true;
	}
	public boolean mouseMove(Event e,int x,int y)
	{
		showStatus("当前鼠标坐标("+x+","+y+")");
		return true;
	}
	
	public boolean mouseExit(Event e,int x,int y)
	{
		showStatus("鼠标已经离开绘图区");
		return true;
	}
	
	public boolean mouseDrag(Event e,int x,int y)
	{
	x1=x;
	y1=y;
	showStatus("当前鼠标坐标("+x+","+y+")鼠标正在拖动....");
	return true;
	}
	public void update(Graphics g)
	{
		if(downmouse)
			paintx(g);
	     	if(firstdone&&(!downmouse)&&upmouse) 
			paint(g);
	}
	public void paint(Graphics g)//画线
	{
		g.setColor(Color.white);
	
		g.drawLine(x1,y1,x2,y2);
		
	}
	public void paintx(Graphics g)//画叉；
	{
		Graphics2D gg = (Graphics2D)g; 
		gg.setStroke(new BasicStroke(4.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND)); 
		g.setColor(Color.red);
		g.drawLine(x1+5,y1-5,x1-5,y1+5);
		g.drawLine(x1-5,y1-5,x1+5,y1+5);
		gg.setStroke(new BasicStroke()); 
		downmouse=false;
	}

}