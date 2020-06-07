import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
public class Boat extends JPanel implements ActionListener{

	Timer tm1 = new Timer(10,this);
	int x=0,velx=2;
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		
		int h1[]={0,150,350,450,600};
		int h2[]={350,100,300,100,350};
		g.setColor(Color.green);
		g.fillPolygon(h1,h2,5);
		g.setColor(Color.yellow);
		g.fillOval(10, 10, 50, 50);
		g.setColor(Color.blue);
		g.fillRect(0, 350, 600, 50);
		g.setColor(Color.black);
		int a[]={x,x+30,x+90,x+120};
		int b[]={300,350,350,300};
		g.fillPolygon(a,b,4);
		g.setColor(Color.black);
		g.drawLine(x+90,300,x+90,250);
		int t1[]={x+90,x+90,x+60};
		int t2[]={270,250,270};
		g.setColor(Color.red);
		g.fillPolygon(t1,t2,3);
		
		tm1.start();
	}
	
	
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(x<480)
		x=x+velx;
		repaint();
		if(x==480)
		{	
		    x=0;
		    repaint();
		}
}
	
public static void main(String args[])
{
	Boat b = new Boat();
	JFrame f = new JFrame("hello world");
	f.setSize(600,400);
	f.add(b);
	f.setVisible(true);
}
}
