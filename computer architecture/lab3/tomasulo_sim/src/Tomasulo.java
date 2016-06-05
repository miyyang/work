//请根据你的包路径修改
//package ustc.qyq;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.Reader;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EtchedBorder;

/**
 * @author yanqing.qyq 2012-2015@USTC
 * 模板说明：该模板主要提供依赖Swing组件提供的JPanle，JFrame，JButton等提供的GUI。使用“监听器”模式监听各个Button的事件，从而根据具体事件执行不同方法。
 * Tomasulo算法核心需同学们自行完成，见说明（4）
 * 对于界面必须修改部分，见说明(1),(2),(3)
 *
 *  (1)说明：根据你的设计完善指令设置中的下拉框内容
 *	(2)说明：请根据你的设计指定各个面板（指令状态，保留站，Load部件，寄存器部件）的大小
 *	(3)说明：设置界面默认指令
 *	(4)说明： Tomasulo算法实现
 */

public class Tomasulo extends JFrame implements ActionListener{
    /*
     * 界面上有六个面板：
     * panel1 : 指令设置
     * panel2 : 执行时间设置
     * panel3 : 指令状态
     * panel4 : 保留站状态
     * panel5 : Load部件
     * panel6 : 寄存器状态
     */
    private JPanel panel1,panel2,panel3,panel4,panel5,panel6;

    /*
     * 四个操作按钮：步进，进5步，重置，执行
     */
    private JButton stepbut,step5but,resetbut,startbut;

    /*
     * 指令选择框
     */
    private JComboBox instbox[]=new JComboBox[24];

    /*
     * 每个面板的名称
     */
    private JLabel instl, timel, tl1,tl2,tl3,tl4,resl,regl,ldl,insl,stepsl;
    private int time[]=new int[4];

    /*
     * 部件执行时间的输入框
     */
    private JTextField tt1,tt2,tt3,tt4;

    private int intv[][]=new int[6][4],instnow=0;

    int cnow;

    private int cal[][]={{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}};
    private int ld[][]={{0,0},{0,0},{0,0}};
    private int ff[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	/*
	 * (1)说明：根据你的设计完善指令设置中的下拉框内容
	 * inst： 指令下拉框内容:"NOP","L.D","ADD.D","SUB.D","MULT.D","DIV.D"…………
	 * fx：       目的寄存器下拉框内容:"F0","F2","F4","F6","F8" …………
	 * rx：       源操作数寄存器内容:"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9" …………
	 * ix：       立即数下拉框内容:"0","1","2","3","4","5","6","7","8","9" …………
	 */

    public static int m=0;
    private String  inst[]={"NOP","L.D","ADD.D","SUB.D","MULT.D","DIV.D"},
            fx[]={"F0","F2","F4","F6","F8","F10","F12","F14","F16","F18","F20","F22","F24","F26","F28","F30"},
            rx[]={"R0","R1","R2","R3","R4","R5","R6"},
            ix[]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25"};

	/*
	 * (2)说明：请根据你的设计指定各个面板（指令状态，保留站，Load部件，寄存器部件）的大小
	 * 		指令状态 面板
	 * 		保留站 面板
	 * 		Load部件 面板
	 * 		寄存器 面板
	 * 					的大小
	 */

    /*
     * 指令状态 7 x 4
     * 保留站列表 6 x 8
     * load缓存列表 4 x 4
     * 寄存器列表 3 x 17
     */
    private	String  instst[][]=new String[7][4], resst[][]=new String[6][8],
            ldst[][]=new String[4][4], regst[][]=new String[3][17];
    /* 预存 */
    private String  culinstst[][]=new String[7][4], culresst[][]=new String[6][8],
            culldst[][]=new String[4][4], culregst[][]=new String[3][17];
    private	JLabel  instjl[][]=new JLabel[7][4], resjl[][]=new JLabel[6][8],
            ldjl[][]=new JLabel[4][4], regjl[][]=new JLabel[3][17];

    /* 指令队列 */
    private Instruction instruction[] = new Instruction[6];
    /* 指令状态 */
    private InstructionState instructionstate[] = new InstructionState[6];
    /* 保留站 */
    private ReservationStation reservationstation[] = new ReservationStation[5];
    /* load缓存 */
    private LoadBuffer loadbuffer[] = new LoadBuffer[3];
    /* 寄存器站 */
    private RegisterStation RegS[] = new RegisterStation[16];


    //构造方法
    private Tomasulo(){
        super("Tomasulo Simulator");

        //设置布局
        Container cp=getContentPane();
        FlowLayout layout=new FlowLayout();
        cp.setLayout(layout);

        //指令设置。GridLayout(int 指令条数, int 操作码+操作数, int hgap, int vgap)
        instl = new JLabel("指令设置");
        panel1 = new JPanel(new GridLayout(6,4,0,0));
        panel1.setPreferredSize(new Dimension(350, 150));
        panel1.setBorder(new EtchedBorder(EtchedBorder.RAISED));

        //操作按钮:执行，重设，步进，步进5步
        timel = new JLabel("执行时间设置");
        panel2 = new JPanel(new GridLayout(2,4,0,0));
        panel2.setPreferredSize(new Dimension(280, 80));
        panel2.setBorder(new EtchedBorder(EtchedBorder.RAISED));

        //指令状态
        insl = new JLabel("指令状态");
        panel3 = new JPanel(new GridLayout(7,4,0,0));
        panel3.setPreferredSize(new Dimension(420, 175));
        panel3.setBorder(new EtchedBorder(EtchedBorder.RAISED));

        //保留站
        resl = new JLabel("保留站");
        panel4 = new JPanel(new GridLayout(6,7,0,0));
        panel4.setPreferredSize(new Dimension(420, 150));
        panel4.setBorder(new EtchedBorder(EtchedBorder.RAISED));

        //Load部件
        ldl = new JLabel("Load部件");
        panel5 = new JPanel(new GridLayout(4,4,0,0));
        panel5.setPreferredSize(new Dimension(200, 100));
        panel5.setBorder(new EtchedBorder(EtchedBorder.RAISED));

        //寄存器状态
        regl = new JLabel("寄存器");
        panel6 = new JPanel(new GridLayout(3,17,0,0));
        panel6.setPreferredSize(new Dimension(740, 75));
        panel6.setBorder(new EtchedBorder(EtchedBorder.RAISED));

        tl1 = new JLabel("Load");
        tl2 = new JLabel("加/减");
        tl3 = new JLabel("乘法");
        tl4 = new JLabel("除法");

        //操作按钮:执行，重设，步进，步进5步
        stepsl = new JLabel();
        stepsl.setPreferredSize(new Dimension(200, 30));
        stepsl.setHorizontalAlignment(SwingConstants.CENTER);
        stepsl.setBorder(new EtchedBorder(EtchedBorder.RAISED));
        stepbut = new JButton("步进");
        stepbut.addActionListener(this);
        step5but = new JButton("步进5步");
        step5but.addActionListener(this);
        startbut = new JButton("执行");
        startbut.addActionListener(this);
        resetbut= new JButton("重设");
        resetbut.addActionListener(this);
        tt1 = new JTextField("2");
        tt2 = new JTextField("2");
        tt3 = new JTextField("10");
        tt4 = new JTextField("40");

        //指令设置
		/*
		 * 设置指令选择框（操作码，操作数，立即数等）的default选择
		 */
        for (int i=0;i<2;i++)
            for (int j=0;j<4;j++){
                if (j==0){
                    instbox[i*4+j]=new JComboBox(inst);
                }
                else if (j==1){
                    instbox[i*4+j]=new JComboBox(fx);
                }
                else if (j==2){
                    instbox[i*4+j]=new JComboBox(ix);
                }
                else {
                    instbox[i*4+j]=new JComboBox(rx);
                }
                instbox[i*4+j].addActionListener(this);
                panel1.add(instbox[i*4+j]);
            }
        for (int i=2;i<6;i++)
            for (int j=0;j<4;j++){
                if (j==0){
                    instbox[i*4+j]=new JComboBox(inst);
                }
                else {
                    instbox[i*4+j]=new JComboBox(fx);
                }
                instbox[i*4+j].addActionListener(this);
                panel1.add(instbox[i*4+j]);
            }
		/*
		 * (3)说明：设置界面默认指令，根据你设计的指令，操作数等的选择范围进行设置。
		 * 默认6条指令。待修改
		 */
		/*L.D F6,21(R2)*/
        instbox[0].setSelectedIndex(1);
        instbox[1].setSelectedIndex(3);
        instbox[2].setSelectedIndex(21);
        instbox[3].setSelectedIndex(2);
        /*L.D F2,20(R3)*/
        instbox[4].setSelectedIndex(1);
        instbox[5].setSelectedIndex(1);
        instbox[6].setSelectedIndex(20);
        instbox[7].setSelectedIndex(3);
        /*MUL.D F0,F2,F4*/
        instbox[8].setSelectedIndex(4);
        instbox[9].setSelectedIndex(0);
        instbox[10].setSelectedIndex(1);
        instbox[11].setSelectedIndex(2);
        /*SUB.D F8,F6,F2*/
        instbox[12].setSelectedIndex(3);
        instbox[13].setSelectedIndex(4);
        instbox[14].setSelectedIndex(3);
        instbox[15].setSelectedIndex(1);
        /*DIV.D F10,F0,F6*/
        instbox[16].setSelectedIndex(5);
        instbox[17].setSelectedIndex(5);
        instbox[18].setSelectedIndex(0);
        instbox[19].setSelectedIndex(3);
        /*ADD.D F6,F8,F2*/
        instbox[20].setSelectedIndex(2);
        instbox[21].setSelectedIndex(3);
        instbox[22].setSelectedIndex(4);
        instbox[23].setSelectedIndex(1);

        //执行时间设置
        panel2.add(tl1);
        panel2.add(tt1);
        panel2.add(tl2);
        panel2.add(tt2);
        panel2.add(tl3);
        panel2.add(tt3);
        panel2.add(tl4);
        panel2.add(tt4);

        //指令状态设置
        for (int i=0;i<7;i++)
        {
            for (int j=0;j<4;j++){
                instjl[i][j]=new JLabel(instst[i][j]);
                instjl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
                panel3.add(instjl[i][j]);
            }
        }
        //保留站设置
        for (int i=0;i<6;i++)
        {
            for (int j=0;j<8;j++){
                resjl[i][j]=new JLabel(resst[i][j]);
                resjl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
                panel4.add(resjl[i][j]);
            }
        }
        //Load部件设置
        for (int i=0;i<4;i++)
        {
            for (int j=0;j<4;j++){
                ldjl[i][j]=new JLabel(ldst[i][j]);
                ldjl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
                panel5.add(ldjl[i][j]);
            }
        }
        //寄存器设置
        for (int i=0;i<3;i++)
        {
            for (int j=0;j<17;j++){
                regjl[i][j]=new JLabel(regst[i][j]);
                regjl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
                panel6.add(regjl[i][j]);
            }
        }

        //向容器添加以上部件
        cp.add(instl);
        cp.add(panel1);
        cp.add(timel);
        cp.add(panel2);

        cp.add(startbut);
        cp.add(resetbut);
        cp.add(stepbut);
        cp.add(step5but);

        cp.add(panel3);
        cp.add(insl);
        cp.add(panel5);
        cp.add(ldl);
        cp.add(panel4);
        cp.add(resl);
        cp.add(stepsl);
        cp.add(panel6);
        cp.add(regl);

        stepbut.setEnabled(false);
        step5but.setEnabled(false);
        panel3.setVisible(false);
        insl.setVisible(false);
        panel4.setVisible(false);
        ldl.setVisible(false);
        panel5.setVisible(false);
        resl.setVisible(false);
        stepsl.setVisible(false);
        panel6.setVisible(false);
        regl.setVisible(false);
        setSize(820,620);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    /*
     * 点击”执行“按钮后，根据选择的指令，初始化其他几个面板
     */
    private void init(){
        // get value
        for (int i=0;i<6;i++){
            intv[i][0]=instbox[i*4].getSelectedIndex();
            if (intv[i][0]!=0){
                intv[i][1]=2*instbox[i*4+1].getSelectedIndex();
				/*load选择fx,ix,rx*/
                if (intv[i][0]==1){
                    intv[i][2]=instbox[i*4+2].getSelectedIndex();
                    intv[i][3]=instbox[i*4+3].getSelectedIndex();
                }
				/*算术运算指令选择fx,fx,fx*/
                else {
                    intv[i][2]=2*instbox[i*4+2].getSelectedIndex();
                    intv[i][3]=2*instbox[i*4+3].getSelectedIndex();
                }
            }
        }

        time[0]=Integer.parseInt(tt1.getText());
        time[1]=Integer.parseInt(tt2.getText());
        time[2]=Integer.parseInt(tt3.getText());
        time[3]=Integer.parseInt(tt4.getText());
        //System.out.println(time[0]);
        // set 0
        instst[0][0]="指令";
        instst[0][1]="流出";
        instst[0][2]="执行";
        instst[0][3]="写回";


        ldst[0][0]="名称";
        ldst[0][1]="Busy";
        ldst[0][2]="地址";
        ldst[0][3]="值";
        ldst[1][0]="Load1";
        ldst[2][0]="Load2";
        ldst[3][0]="Load3";
        ldst[1][1]="no";
        ldst[2][1]="no";
        ldst[3][1]="no";

        resst[0][0]="Time";
        resst[0][1]="名称";
        resst[0][2]="Busy";
        resst[0][3]="Op";
        resst[0][4]="Vj";
        resst[0][5]="Vk";
        resst[0][6]="Qj";
        resst[0][7]="Qk";
        resst[1][1]="Add1";
        resst[2][1]="Add2";
        resst[3][1]="Add3";
        resst[4][1]="Mult1";
        resst[5][1]="Mult2";
        resst[1][2]="no";
        resst[2][2]="no";
        resst[3][2]="no";
        resst[4][2]="no";
        resst[5][2]="no";

        regst[0][0]="字段";
        for (int i=1;i<17;i++){
            //System.out.print(i+" "+fx[i-1];
            regst[0][i]=fx[i-1];

        }
        regst[1][0]="状态";
        regst[2][0]="值";

        /* 展示 指令的 指令名称、目的寄存器、源操作数1、源操作数2 */
        /* 初始化指令状态 */
        for (int i=1;i<7;i++)
        {
            instruction[i-1] = new Instruction();
            for (int j=0;j<4;j++){
                if (j==0){
                    int temp=i-1;
                    String disp;
                    disp = inst[instbox[temp*4].getSelectedIndex()]+" ";
                    // nop int
                    if (instbox[temp*4].getSelectedIndex()==0)
                    {
                        instruction[i-1].name=inst[instbox[temp*4].getSelectedIndex()];
                        instruction[i-1].opr1=fx[instbox[temp*4+1].getSelectedIndex()];
                        instruction[i-1].opr2=fx[instbox[temp*4+2].getSelectedIndex()];
                        instruction[i-1].opr3=fx[instbox[temp*4+3].getSelectedIndex()];
                    }
                    // load ins
                    else if (instbox[temp*4].getSelectedIndex()==1)
                    {
                        disp=disp+fx[instbox[temp*4+1].getSelectedIndex()]+','+
                                ix[instbox[temp*4+2].getSelectedIndex()]+'('+rx[instbox[temp*4+3].getSelectedIndex()]+')';
                        instruction[i-1].name=inst[instbox[temp*4].getSelectedIndex()];
                        instruction[i-1].opr1=fx[instbox[temp*4+1].getSelectedIndex()];
                        instruction[i-1].opr2=ix[instbox[temp*4+2].getSelectedIndex()];
                        instruction[i-1].opr3=rx[instbox[temp*4+3].getSelectedIndex()];
                    }
                    // cal ins
                    else
                    {
                        disp=disp+fx[instbox[temp*4+1].getSelectedIndex()]+','+
                                fx[instbox[temp*4+2].getSelectedIndex()]+','+fx[instbox[temp*4+3].getSelectedIndex()];
                        instruction[i-1].name=inst[instbox[temp*4].getSelectedIndex()];
                        instruction[i-1].opr1=fx[instbox[temp*4+1].getSelectedIndex()];
                        instruction[i-1].opr2=fx[instbox[temp*4+2].getSelectedIndex()];
                        instruction[i-1].opr3=fx[instbox[temp*4+3].getSelectedIndex()];
                    }
                    instst[i][j]=disp;
                }
                else instst[i][j]="";
            }

            instructionstate[i-1]=new InstructionState();
            instructionstate[i-1].state=0;
            instructionstate[i-1].instruction=instruction[i-1];
            instructionstate[i-1].excutetime=getTimeForEX(instruction[i-1]);
        }

        for (int i=1;i<6;i++)
            for (int j=0;j<8;j++)if (j!=1&&j!=2){
                resst[i][j]="";
            }
        for (int i=1;i<4;i++)
            for (int j=2;j<4;j++){
                ldst[i][j]="";
            }
        for (int i=1;i<3;i++)
            for (int j=1;j<17;j++){
                regst[i][j]="";
            }
        instnow=0;
        for (int i=0;i<5;i++){
            for (int j=1;j<3;j++) cal[i][j]=0;
            cal[i][0]=-1;
        }
		/* ld可对ldst写 */
        for (int i=0;i<3;i++)
            for (int j=0;j<2;j++)
                ld[i][j]=0;
		/* ff可对regst写 */
        for (int i=0;i<17;i++)
            ff[i]=0;


        /**
         * 初始化 保留站/寄存器站/load缓存
         */
        for(int i=0;i<5;i++)
        {
            reservationstation[i]=new ReservationStation();
            reservationstation[i].Qi=resst[i+1][1];
            reservationstation[i].Busy=resst[i+1][2];
            reservationstation[i].Op=resst[i+1][3];
            reservationstation[i].Vj=resst[i+1][4];
            reservationstation[i].Vk=resst[i+1][5];
            reservationstation[i].Qj=resst[i+1][6];
            reservationstation[i].Qk=resst[i+1][7];
        }
        for(int i=0;i<3;i++)
        {
            loadbuffer[i]=new LoadBuffer();
            loadbuffer[i].Qi=ldst[i+1][0];
            loadbuffer[i].Busy=ldst[i+1][1];
            loadbuffer[i].Addr=ldst[i+1][2];
            loadbuffer[i].value=ldst[i+1][3];
        }
        for(int i=0;i<16;i++)
        {
            RegS[i]=new RegisterStation();
            RegS[i].state=regst[0][i+1];
            RegS[i].Qi=regst[1][i+1];
            RegS[i].value=regst[2][i+1];
        }
    }

    // 获取执行时间
    private int getTimeForEX(Instruction instruction){
        if(instruction.name.equals("L.D"))
        {
            return Integer.parseInt(tt1.getText());
            //return 2;
        }
        else if(instruction.name.equals("ADD.D") || instruction.name.equals("SUB.D"))
        {
            return Integer.parseInt(tt2.getText());
            //return 2;
        }
        else if(instruction.name.equals("MULT.D"))
        {
            return Integer.parseInt(tt3.getText());
            //return 10;
        }
        else if(instruction.name.equals("DIV.D"))
        {
            return Integer.parseInt(tt4.getText());
            //return 40;
        }
        else {
            return 0;
        }
    }

    /*
     * 点击操作按钮后，用于显示结果
     */
    public void display(){
        for (int i=0;i<7;i++)
            for (int j=0;j<4;j++){
                instjl[i][j].setText(instst[i][j]);
            }
        for (int i=0;i<6;i++)
            for (int j=0;j<8;j++){
                resjl[i][j].setText(resst[i][j]);
            }
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++){
                ldjl[i][j].setText(ldst[i][j]);
            }
        for (int i=0;i<3;i++)
            for (int j=0;j<17;j++){
                regjl[i][j].setText(regst[i][j]);
            }
        stepsl.setText("当前周期："+String.valueOf(cnow-1));
    }

    public void actionPerformed(ActionEvent e){
        //点击“执行”按钮的监听器
        if (e.getSource()==startbut) {
            for (int i=0;i<24;i++) instbox[i].setEnabled(false);
            tt1.setEnabled(false);tt2.setEnabled(false);
            tt3.setEnabled(false);tt4.setEnabled(false);
            stepbut.setEnabled(true);
            step5but.setEnabled(true);
            startbut.setEnabled(false);
            //根据指令设置的指令初始化其他的面板
            init();
            cnow=1;
            //展示其他面板
            display();
            panel3.setVisible(true);
            panel4.setVisible(true);
            panel5.setVisible(true);
            panel6.setVisible(true);
            insl.setVisible(true);
            ldl.setVisible(true);
            resl.setVisible(true);
            stepsl.setVisible(true);
            regl.setVisible(true);
        }
        //点击“重置”按钮的监听器
        if (e.getSource()==resetbut) {
            m=0;
            for (int i=0;i<24;i++) instbox[i].setEnabled(true);
            tt1.setEnabled(true);tt2.setEnabled(true);
            tt3.setEnabled(true);tt4.setEnabled(true);
            stepbut.setEnabled(false);
            step5but.setEnabled(false);
            startbut.setEnabled(true);
            panel3.setVisible(false);
            insl.setVisible(false);
            panel4.setVisible(false);
            ldl.setVisible(false);
            panel5.setVisible(false);
            resl.setVisible(false);
            stepsl.setVisible(false);
            panel6.setVisible(false);
            regl.setVisible(false);
            // 根据指令设置的指令初始化其他的面板
            init();
            cnow=1;
        }
//点击“步进”按钮的监听器
        if (e.getSource()==stepbut) {
            core();
            cnow++;
            display();
        }
//点击“进5步”按钮的监听器
        if (e.getSource()==step5but) {
            for (int i=0;i<5;i++){
                core();
                cnow++;
            }
            display();
        }

        for (int i=0;i<24;i=i+4)
        {
            if (e.getSource()==instbox[i]) {
                if (instbox[i].getSelectedIndex()==1){
                    instbox[i+2].removeAllItems();
                    for (int j=0;j<ix.length;j++) instbox[i+2].addItem(ix[j]);
                    instbox[i+3].removeAllItems();
                    for (int j=0;j<rx.length;j++) instbox[i+3].addItem(rx[j]);
                }
                else {
                    instbox[i+2].removeAllItems();
                    for (int j=0;j<fx.length;j++) instbox[i+2].addItem(fx[j]);
                    instbox[i+3].removeAllItems();
                    for (int j=0;j<fx.length;j++) instbox[i+3].addItem(fx[j]);
                }
            }
        }
    }

/*
 * (4)说明： Tomasulo算法实现
 */

    public void core()
    {
        // state 0 未发射
        // state 1 已发射但未执行
        // state 2 正在执行但未执行完毕
        // state 3 执行完毕但未写回

        int to_be_issue = this.get_issue(instructionstate);
        int to_be_exec[] = this.get_ready_exec(instructionstate);
        int to_be_done[] = this.get_done_exec(instructionstate);
        int to_be_writeback[] = this.get_writeback(instructionstate);

        // issue
        if(to_be_issue != -1)
        {
            InstructionState inss = instructionstate[to_be_issue];
            // issue load ins
            if(inss.instruction.name.equals("L.D"))
            {
                int load_place = this.avail_load(loadbuffer);
                if(load_place != -1)
                {
                    inss.Qi = loadbuffer[load_place].Qi;
                    loadbuffer[load_place].Busy = "yes";
                    ldst[load_place+1][1] = loadbuffer[load_place].Busy;
                    // 发送rt
                    loadbuffer[load_place].value = inss.instruction.opr2;
                    ldst[load_place+1][3] = loadbuffer[load_place].value;
                    // 不用发送rs, 因为rs是立即数
                }
            }
            // issue fp ins
            else {
                int resv_place = this.avail_resv(instructionstate[to_be_issue], reservationstation);
                if(resv_place != -1)
                {
                    inss.Qi = reservationstation[resv_place].Qi;
                    reservationstation[resv_place].Busy = "yes";
                    resst[resv_place+1][2] = reservationstation[resv_place].Busy;
                    reservationstation[resv_place].Op = inss.instruction.name;
                    resst[resv_place+1][3] = reservationstation[resv_place].Op;

                    // 检查寄存器相关
                    boolean rel_op_j = false;
                    boolean rel_op_k = false;
                    for(int i = 0; i < to_be_issue; i++)
                    {
                        String des;
                        des = instructionstate[i].instruction.opr1;
                        // 发送rt
                        if(inss.instruction.opr2.equals(des))
                        {
                            rel_op_j = true;
                            for(int j = 0;j < RegS.length; j++)
                            {
                                if(RegS[j].state.equals(des))
                                {
                                    if(RegS[j].value.equals(""))
                                    {
                                        reservationstation[resv_place].Qj = RegS[j].Qi;
                                        resst[resv_place+1][6] = reservationstation[resv_place].Qj;
                                    }
                                    else {
                                        reservationstation[resv_place].Vj = RegS[j].value;
                                        resst[resv_place+1][4] = reservationstation[resv_place].Vj;
                                    }
                                }
                            }
                        }
                        // 发送rs
                        if(inss.instruction.opr3.equals(des))
                        {
                            rel_op_k = true;
                            for(int j = 0;j < RegS.length; j++)
                            {
                                if(RegS[j].state.equals(des))
                                {
                                    if(RegS[j].value.equals(""))
                                    {
                                        reservationstation[resv_place].Qk = RegS[j].Qi;
                                        resst[resv_place+1][7] = reservationstation[resv_place].Qk;
                                    }
                                    else {
                                        reservationstation[resv_place].Vk = RegS[j].value;
                                        resst[resv_place+1][5] = reservationstation[resv_place].Vk;
                                    }
                                }
                            }
                        }
                    }
                    // 无寄存器相关
                    if(!rel_op_j)
                    {
                        reservationstation[resv_place].Vj = inss.instruction.opr2;
                        resst[resv_place+1][4] = "R[" + reservationstation[resv_place].Vj + "]";
                    }
                    if(!rel_op_k)
                    {
                        reservationstation[resv_place].Vk = inss.instruction.opr3;
                        resst[resv_place+1][5] = "R[" + reservationstation[resv_place].Vk + "]";
                    }
                }

            }
            // 相应地修改寄存器站
            String opr1,Qi;
            opr1 = inss.instruction.opr1;
            Qi = inss.Qi;
            for(int i = 0; i < this.RegS.length; i++)
            {
                if(RegS[i].state.equals(opr1))
                {
                    RegS[i].Qi = Qi;
                    regst[1][i+1] = RegS[i].Qi;
                    break;
                }
            }
            // 修改指令状态
            instst[to_be_issue+1][1] = String.valueOf(cnow);
            instructionstate[to_be_issue].state = 1;
        }

        // exec 1
        for(int i = 0; i < to_be_exec.length; i++)
        {
            if(to_be_exec[i] != -1)
            {
                InstructionState inss = instructionstate[to_be_exec[i]];
                // load ins
                if(inss.instruction.name.equals("L.D"))
                {
                    for(int j = 0; j < loadbuffer.length; j++)
                    {
                        if(loadbuffer[j].Qi.equals(inss.Qi))
                        {
                            // 计算有效地址
                            loadbuffer[j].Addr = "R[" + inss.instruction.opr3 + "]" + inss.instruction.opr2;
                            ldst[j+1][2] = loadbuffer[j].Addr;
                            inss.excutetime--;
                            break;
                        }
                    }
                    // wait until load step 1 complete
                    if(inss.excutetime > 0)
                    {
                        instst[to_be_exec[i]+1][2] = String.valueOf(cnow)+"->";
                        instructionstate[to_be_exec[i]].state = 2;
                    }
                    else if(inss.excutetime == 0)
                    {
                        instst[to_be_exec[i]+1][2] = String.valueOf(cnow);
                        instructionstate[to_be_exec[i]].state = 3;
                    }
                }
                // fp ins
                else {
                    String Qi2 = inss.Qi;
                    for(int j = 0; j < reservationstation.length; j++)
                    {
                        if(reservationstation[j].Qi.equals(inss.Qi))
                        {
                            if(!reservationstation[j].Vj.equals("") && !reservationstation[j].Vk.equals(""))
                            {
                                inss.excutetime--;
                                resst[j+1][0] = String.valueOf(inss.excutetime);
                                // wait until load step 1 complete
                                if(inss.excutetime > 0)
                                {
                                    instst[to_be_exec[i]+1][2] = String.valueOf(cnow)+"->";
                                    instructionstate[to_be_exec[i]].state = 2;
                                    break;
                                }
                                else if(inss.excutetime == 0)
                                {
                                    instst[to_be_exec[i]+1][2] = String.valueOf(cnow);
                                    instructionstate[to_be_exec[i]].state = 3;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        // exec 2
        for(int i = 0; i < to_be_done.length; i++)
        {
            if(to_be_done[i] != -1)
            {
                InstructionState inss = instructionstate[to_be_done[i]];
                // load ins
                if(inss.instruction.name.equals("L.D"))
                {
                    // read from mem
                    for(int j = 0; j < loadbuffer.length; j++)
                    {
                        if(loadbuffer[j].Qi.equals(inss.Qi))
                        {
                            loadbuffer[j].value = "M[" + loadbuffer[j].Addr + "]";
                            ldst[j+1][3] = loadbuffer[j].value;
                            inss.excutetime--;
                            break;
                        }
                    }
                    if(inss.excutetime == 0)
                    {
                        instst[to_be_done[i]+1][2] += String.valueOf(cnow);
                        instructionstate[to_be_done[i]].state = 3;
                    }
                }
                // fp ins
                else {
                    int j;
                    for(j = 0; j < reservationstation.length; j++)
                    {
                        if(reservationstation[j].Qi.equals(inss.Qi))
                        {
                            inss.excutetime--;
                            resst[j+1][0] = String.valueOf(inss.excutetime);
                            break;
                        }
                    }
                    if(inss.excutetime == 0)
                    {
                        instst[to_be_done[i]+1][2] += String.valueOf(cnow);
                        instructionstate[to_be_done[i]].state = 3;
                        resst[j+1][0] = "";
                    }
                }
            }
        }

        // write back
        for(int i = 0; i < to_be_writeback.length; i++)
        {
            if(to_be_writeback[i] != -1)
            {
                InstructionState inss = instructionstate[to_be_writeback[i]];
                String Qi4 = inss.Qi;
                // load ins
                // 写回并释放load buffer
                if(inss.instruction.name.equals("L.D"))
                {
                    for(int j = 0; j < loadbuffer.length; j++)
                    {
                        if(loadbuffer[j].Qi.equals(inss.Qi))
                        {
                            loadbuffer[j].Busy = "no";
                            loadbuffer[j].Addr = "";
                            loadbuffer[j].value = "";
                            ldst[j+1][1] = loadbuffer[j].Busy;
                            ldst[j+1][2] = loadbuffer[j].Addr;
                            ldst[j+1][3] = loadbuffer[j].value;
                            break;
                        }
                    }
                }
                // fp ins
                // 释放reservation station
                else {
                    for(int j = 0; j < reservationstation.length; j++)
                    {
                        if(reservationstation[j].Qi.equals(Qi4))
                        {
                            reservationstation[j].Busy = "no";
                            reservationstation[j].Op = "";
                            reservationstation[j].Qj = "";
                            reservationstation[j].Qk = "";
                            reservationstation[j].Vj = "";
                            reservationstation[j].Vk = "";
                            resst[j+1][2] = reservationstation[j].Busy;
                            for(int k = 3; k < 8; k++)
                                resst[j+1][k] = "";
                            break;
                        }
                    }
                }
                // update regs
                for(int j = 0; j < RegS.length; j++)
                {
                    if(RegS[j].Qi.equals(Qi4))
                    {
                        m++;
                        RegS[j].value = "M"+m;
                        regst[2][j+1] = RegS[j].value;
                    }
                }
                // update rs & rt in reservationstation
                for(int j = 0; j < reservationstation.length; j++)
                {
                    if(reservationstation[j].Qj.equals(Qi4))
                    {
                        reservationstation[j].Vj = "M" + m;
                        reservationstation[j].Qj = "";
                        resst[j+1][4] = reservationstation[j].Vj;
                        resst[j+1][6] = reservationstation[j].Qj;
                        continue;
                    }
                    if(reservationstation[j].Qk.equals(Qi4))
                    {
                        reservationstation[j].Vk = "M"+m;
                        reservationstation[j].Qk = "";
                        resst[j+1][5] = reservationstation[j].Vk;
                        resst[j+1][7] = reservationstation[j].Qk;
                    }
                }
                instst[to_be_writeback[i]+1][3] = String.valueOf(cnow);
                instructionstate[to_be_writeback[i]].state = 4;
            }
        }

        boolean completed = true;
        for(int l = 0; l < instructionstate.length; l++)
        {
            if(!instructionstate[l].instruction.name.equals("NOP") && instst[l+1][3].equals(""))
            {
                completed = false;
                break;
            }
        }
        if(completed)
        {
            stepbut.setEnabled(false);
            step5but.setEnabled(false);
        }

    }

    // 找到可用load缓存的编号
    private int avail_load(LoadBuffer loadbuffer[]){
        int num_idld=-1;
        for(int i=0;i<loadbuffer.length;i++)
        {
            if(loadbuffer[i].Busy.equals("no"))
            {
                num_idld=i;
                break;
            }
        }
        return num_idld;
    }

    // 找到可用运算部件的编号
    private int avail_resv(InstructionState instructionstate,ReservationStation reservationstation[])
    {
        int resv_place=-1;

        if(instructionstate.instruction.name.equals("MULT.D") || instructionstate.instruction.name.equals("DIV.D"))
        {
            for(int i=3;i<5;i++)
            {
                if(reservationstation[i].Busy.equals("no"))
                {
                    resv_place=i;
                    break;
                }
            }
        }
        else if(instructionstate.instruction.name.equals("ADD.D") || instructionstate.instruction.name.equals("SUB.D"))
        {
            for(int i=0;i<3;i++)
            {
                if(reservationstation[i].Busy.equals("no"))
                {
                    resv_place=i;
                    break;
                }
            }
        }
        return resv_place;
    }

    // 找到待写回的指令的编号
    private int[] get_writeback(InstructionState instructionstate[]) {
        int n=0;
        for(int i=0;i<instructionstate.length;i++)
        {
            if(instructionstate[i].state==3 && !instructionstate[i].instruction.name.equals("NOP"))
            {
                n++;
            }
        }
        int to_be_writeback[] = new int[n];
        for(int i=0;i<n;i++)
        {
            to_be_writeback[i]=-1;
        }
        for(int i=0,j=0;i<instructionstate.length;i++)
        {
            if(instructionstate[i].state==3 && !instructionstate[i].instruction.name.equals("NOP"))
            {
                to_be_writeback[j]=i;
                j++;
            }
        }
        return to_be_writeback;
    }

    // 找到待执行完毕的指令的编号
    private int[] get_done_exec(InstructionState instructionstate[]) {
        int n=0;
        for(int i=0;i<instructionstate.length;i++)
        {
            if(instructionstate[i].state==2 && !instructionstate[i].instruction.name.equals("NOP"))
            {
                n++;
            }
        }
        int to_be_done[] = new int[n];
        for(int i=0;i<n;i++)
        {
            to_be_done[i]=-1;
        }
        for(int i=0,j=0;i<instructionstate.length;i++)
        {
            if(instructionstate[i].state==2 && !instructionstate[i].instruction.name.equals("NOP"))
            {
                to_be_done[j]=i;
                j++;
            }
        }
        return to_be_done;
    }

    // 找到待执行的指令的编号
    private int[] get_ready_exec(InstructionState instructionstate[]) {
        int n=0;
        for(int i=0;i<instructionstate.length;i++)
            if(instructionstate[i].state==1 && !instructionstate[i].instruction.name.equals("NOP"))
                n++;
        int to_be_exec[] = new int[n];
        for(int i=0;i<n;i++)
        {
            to_be_exec[i]=-1;
        }
        for(int i=0,j=0;i<instructionstate.length;i++)
            if(instructionstate[i].state==1 && !instructionstate[i].instruction.name.equals("NOP"))
            {
                to_be_exec[j]=i;
                j++;
            }
        return to_be_exec;
    }

    // 找到待发射的指令的编号
    private int get_issue(InstructionState instructionstate[]) {
        int to_be_issue=-1;
        for(int i=0;i<instructionstate.length;i++)
        {
            if(instructionstate[i].state==0 && !instructionstate[i].instruction.name.equals("NOP"))
            {
                to_be_issue=i;
                break;
            }
        }
        return to_be_issue;
    }

    // inner class

    private class LoadBuffer{
        String Qi;
        String Busy;
        String Addr;
        String value;
    }

    private class InstructionState{
        String Qi;
        int state;
        int excutetime;
        Instruction instruction;
    }

    private class Instruction{
        String name;
        String opr1;
        String opr2;
        String opr3;
    }

    private class RegisterStation{
        String Qi;
        String value;
        String state;
    }

    private class ReservationStation{
        String Qi;
        String Vj;
        String Vk;
        String Qj;
        String Qk;
        String Op;
        String Busy;
    }

    public static void main(String[] args) {
        new Tomasulo();
    }
}



