
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.applet.*;
import java.util.Vector;
import java.util.Vector;

//*********************主类**********************************
public class MyDraw extends Applet{
    DrawPanel panel;
    StatusBar status;

    public void init() {
	setLayout(new BorderLayout());
	panel = new DrawPanel();
        status = new StatusBar(panel);
	add("Center", panel);
	add("South",status);
    }

    public void destroy() {
        remove(panel);
        remove(status);
    }
//=======================主函数====================
    public static void main(String args[]) {
	JFrame f = new JFrame("MyDraw");
	MyDraw MyDraw = new MyDraw();
	MyDraw.init();
	MyDraw.start();
	f.setTitle("绘图程序"); 
	f.add("Center", MyDraw);
	f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
	f.setBounds(300, 150, 400, 400); 
	f.setVisible(true);
    }
    
}
//******************************主类结束*********************************

//================绘图面板类===============================
class DrawPanel extends Panel implements MouseListener, MouseMotionListener 
{
	
	Vector lines = new Vector();
	
	int x1,y1;
	int x2,y2;
	
	public DrawPanel() 
	{
		setBackground(new Color(170,180,220));
		addMouseMotionListener(this);
		addMouseListener(this);
	}

	public void mouseDragged(MouseEvent e) 
	{
       		e.consume();
       		x2 = e.getX();
                y2 = e.getY();
		repaint();
    	}
	public void mouseMoved(MouseEvent e)
	{
	}
	
	public void mousePressed(MouseEvent e) 
	{
        	e.consume();
		x1 = e.getX();
                y1 = e.getY();
                x2 = -1;
	}

	public void mouseReleased(MouseEvent e) 
	{
		e.consume();
	
		lines.addElement(new Rectangle(x1, y1, e.getX(), e.getY()));
        	x2 = -1;
                
		repaint();
	}

	public void mouseEntered(MouseEvent e){}
	
	public void mouseExited(MouseEvent e){}
 
	public void mouseClicked(MouseEvent e){}

	public void paint(Graphics g) 
	{	
		Graphics2D gg = (Graphics2D)g; 

		int np = lines.size();
		
		for (int i=0; i < np; i++) 
			{
				Rectangle p = (Rectangle)lines.elementAt(i);
				
				gg.setStroke(new BasicStroke(4.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND)); 
				g.setColor(Color.red);
				g.drawLine(p.x+5,p.y-5,p.x-5,p.y+5);
				g.drawLine(p.x-5,p.y-5,p.x+5,p.y+5);
				gg.setStroke(new BasicStroke()); 
				
				g.setColor(Color.green);
				g.drawLine(p.x, p.y, p.width, p.height);
					
	    		}
	
		if (x2 != -1)    g.drawLine(x1, y1, x2, y2);

    }
}

//****************************************************************************
class StatusBar extends JLabel implements MouseMotionListener  {
    DrawPanel target;
	int xx;
	int yy;
    public StatusBar(DrawPanel target) {
	this.target = target;
	setLayout(new FlowLayout());
	this.setBorder(new BevelBorder(BevelBorder.LOWERED));
	setText("当前鼠标坐标("+xx+","+yy+")");
	
    }
	public void mouseMoved(MouseEvent e) 
	{
	if (e.getSource() instanceof DrawPanel) 
		{
			xx=e.getX();
			yy=e.getY();
		}
	}
	public void mouseDragged(MouseEvent e) {}
	

	
}




