using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Catalog
{
    public partial class Form1 : Form
    {

        public struct Cache
        {
            public int addrOfMem, status;
        };
        private Cache[][] cache = new Cache[4][];
        public struct Mem
        {
            public int []list;
            public int status;
        };
        private Mem[][] mem = new Mem[4][];
        private System.Windows.Forms.DataGridView[] dataGridView = new System.Windows.Forms.DataGridView[8];
        private System.Windows.Forms.TextBox[] textBox = new System.Windows.Forms.TextBox[4];
        private System.Windows.Forms.ComboBox[] comboBox = new System.Windows.Forms.ComboBox[4];
        private System.Drawing.Color invalid, shared, modified, unbuffered, animated,animated2;
        public Form1()
        {
            InitializeComponent();
            invalid = SystemColors.ActiveBorder;
            shared = System.Drawing.Color.Cyan;
            modified = System.Drawing.Color.Red;
            unbuffered = System.Drawing.Color.Yellow;
            animated = System.Drawing.Color.Pink;
            animated2 = System.Drawing.Color.Peru;

            int i, j, k;
            comboBox5.SelectedIndex = 0;
            dataGridView[0] = this.dataGridView1;
            dataGridView[1] = this.dataGridView2;
            dataGridView[2] = this.dataGridView3;
            dataGridView[3] = this.dataGridView4;
            dataGridView[4] = this.dataGridView5;
            dataGridView[5] = this.dataGridView6;
            dataGridView[6] = this.dataGridView7;
            dataGridView[7] = this.dataGridView8;
            textBox[0] = this.textBox1;
            textBox[1] = this.textBox2;
            textBox[2] = this.textBox3;
            textBox[3] = this.textBox4;
            comboBox[0] = this.comboBox1;
            comboBox[1] = this.comboBox2;
            comboBox[2] = this.comboBox3;
            comboBox[3] = this.comboBox4;

            for (i = 0; i < 4; i++)
            {
                dataGridView[i].AutoResizeRows(DataGridViewAutoSizeRowsMode.AllCells);
                dataGridView[i].AllowUserToAddRows = false;
                dataGridView[i].AllowUserToDeleteRows = false;
                dataGridView[i].ReadOnly = true;
                dataGridView[i].Rows.Add("0", "");
                dataGridView[i].Rows.Add("1", "");
                dataGridView[i].Rows.Add("2", "");
                dataGridView[i].Rows.Add("3", "");

                dataGridView[i].Rows[0].Cells[1].Style.BackColor = invalid;
                dataGridView[i].Rows[1].Cells[1].Style.BackColor = invalid;
                dataGridView[i].Rows[2].Cells[1].Style.BackColor = invalid;
                dataGridView[i].Rows[3].Cells[1].Style.BackColor = invalid;
            }
            for (i = 4; i < 8; i++)
            {
                dataGridView[i].AutoResizeRows(DataGridViewAutoSizeRowsMode.AllCells);
                dataGridView[i].AllowUserToAddRows = false;
                dataGridView[i].AllowUserToDeleteRows = false;
                dataGridView[i].ReadOnly = true;
                for (j = 0; j < 8; j++)
                {
                    dataGridView[i].Rows.Add((j + (i - 4) * 8).ToString(), "");
                    dataGridView[i].Rows[j].Cells[2].Style.BackColor = unbuffered;
                }

            }
            comboBox1.SelectedIndex = 0;
            comboBox2.SelectedIndex = 0;
            comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 0;
            textBox1.Text = "0";
            textBox2.Text = "0";
            textBox3.Text = "0";
            textBox4.Text = "0";

            for (i = 0; i < 4; i++)
            {
                cache[i] = new Cache[4];
                for (j = 0; j < 4; j++)
                {
                    cache[i][j].addrOfMem = -1;
                    cache[i][j].status = 0;
                }
            }
            for (i = 0; i < 4; i++)
            {
                mem[i] = new Mem[8];
                for (j = 0; j < 8; j++)
                {
                    mem[i][j].status = 0;
                    mem[i][j].list = new int[4];
                    for (k = 0; k < 4; k++)
                    {
                        mem[i][j].list[k] = 0;
                    }
                }
            }
        }

        // actiond 和 actions 实现动画效果
        private void actiond(int x, int y, int p, int q, string str1,string str2)
        {
            System.Drawing.Color c1 = dataGridView[x].Rows[y].Cells[1].Style.BackColor;
            System.Drawing.Color c2 = dataGridView[p].Rows[q].Cells[1].Style.BackColor;
            dataGridView[x].Rows[y].Cells[1].Style.BackColor = animated;
            dataGridView[p].Rows[q].Cells[1].Style.BackColor = animated2;
            dataGridView[x].Rows[y].Cells[1].Value = str1;
            dataGridView[p].Rows[q].Cells[1].Value = str2;
            dataGridView[x].Refresh();
            dataGridView[p].Refresh();
            System.Threading.Thread.Sleep(200);
            dataGridView[x].Rows[y].Cells[1].Style.BackColor = c1;
            dataGridView[p].Rows[q].Cells[1].Style.BackColor = c2;
            dataGridView[x].Rows[y].Cells[1].Value = "";
            dataGridView[p].Rows[q].Cells[1].Value = "";
            dataGridView[x].Refresh();
            dataGridView[p].Refresh();
            System.Threading.Thread.Sleep(100);
            return;
        }
        private void actions(int p, int q, string flash)
        {
            System.Drawing.Color c = dataGridView[p].Rows[q].Cells[1].Style.BackColor;
            dataGridView[p].Rows[q].Cells[1].Style.BackColor = animated;
            dataGridView[p].Rows[q].Cells[1].Value = flash;
            dataGridView[p].Refresh();
            System.Threading.Thread.Sleep(200);
            dataGridView[p].Rows[q].Cells[1].Style.BackColor = c;
            dataGridView[p].Rows[q].Cells[1].Value = "";
            dataGridView[p].Refresh();
            System.Threading.Thread.Sleep(100);
            return;
        }

        private void bling(int p, int q)
        {
            DataGridView dgv = dataGridView[p];
            if (p < 4)
            {
                switch (cache[p][q].status)
                {
                    case 0: dgv.Rows[q].Cells[1].Style.BackColor = invalid; break;
                    case 1: dgv.Rows[q].Cells[1].Style.BackColor = modified; break;
                    case 2: dgv.Rows[q].Cells[1].Style.BackColor = shared; break;
                    default: break;
                }
                if (cache[p][q].status > 0) 
                    dgv.Rows[q].Cells[2].Value = cache[p][q].addrOfMem.ToString();
                else 
                    dgv.Rows[q].Cells[2].Value = "";
            }
            else
            {
                p -= 4;
                switch (mem[p][q].status)
                {
                    case 0: 
                        dgv.Rows[q].Cells[2].Style.BackColor = unbuffered; 
                        break;
                    case 1: 
                        dgv.Rows[q].Cells[2].Style.BackColor = modified; 
                        break;
                    case 2: 
                        dgv.Rows[q].Cells[2].Style.BackColor = shared; 
                        break;
                    default: 
                        break;
                }
                string str1 = "";
                for (int i = 0; i < 4; i++)
                    if (mem[p][q].list[i] > 0)
                        str1 += (Char)(i+'A');
                dgv.Rows[q].Cells[2].Value = str1;
            }
            dgv.Refresh();
        }

        private int get_cache_addr(int i, int addr, int connect)
        {
            int cacheaddr, p, j;
            Random generator = new Random();
            switch (connect)
            {
                case 1:
                    cacheaddr = addr % 4;
                    break;
                case 2:
                    p = addr % 2;
                    for (j = p + p; j <= p + p + 1; j++)
                        if (cache[i][j].addrOfMem == addr)
                            return j;
                    for (j = p + p; j <= p + p + 1; j++)
                        if (cache[i][j].status == 0)
                            return j;
                    j = generator.Next(2);
                    cacheaddr = p + p + j;
                    break;
                case 4:
                    p = addr % 1;
                    for (j = 0; j <= 3; j++)
                        if (cache[i][j].addrOfMem == addr)
                            return j;
                    for (j = 0; j <= 3; j++)
                        if (cache[i][j].status == 0)
                            return j;
                    j = generator.Next(4);
                    cacheaddr = j;
                    break;
                default:
                    cacheaddr = 0;
                    break;
            }
            return cacheaddr;
        }

        private void readmiss(int i,int a,int mi,int ma,int addr){
            actiond(i, a, mi + 4, ma, "读不命中:源", "读不命中:目的");
            if (mem[mi][ma].status == 1)//modified
            {
                int j;
                for (j = 0; j < 4; j++) if (mem[mi][ma].list[j] > 0) break;
                actiond(mi + 4, ma, j, a, "取数据:源", "取数据:目的");
                actiond(j, a, mi + 4, ma, "数据:源", "数据:目的");
                cache[j][a].status = 2;
                bling(j, a);
            }
            actiond(mi + 4, ma, i, a, "数据:源", "数据:目的");
            cache[i][a].status = 2;
            cache[i][a].addrOfMem = addr;
            mem[mi][ma].list[i] = 1;
            mem[mi][ma].status = 2;
            bling(mi + 4, ma);
            bling(i, a);
        }

        private void writemiss(int i, int a, int mi, int ma, int addr)
        {
            actiond(i, a, mi + 4, ma, "写不命中:源", "写不命中:目的");
            if (mem[mi][ma].status == 1)//modified
            {
                int j;
                for (j = 0; j < 4; j++) if (mem[mi][ma].list[j] > 0) break;
                actiond(mi + 4, ma, j, a, "取并作废:源", "取并作废:目的");
                actiond(j, a, mi + 4, ma, "数据:源", "数据:目的");
                mem[mi][ma].list[j] = 0;
                actions(j, a, "作废");
                cache[j][a].status = 0;
                bling(j, a);
            }
            else
            {
                for (int j = 0; j < 4; j++)
                {
                    if (mem[mi][ma].list[j] > 0 && j != i)
                    {
                        actiond(mi + 4, ma, j, a, "作废:源", "作废:目的");
                        mem[mi][ma].list[j] = 0;
                        actions(j, a, "作废");
                        cache[j][a].status = 0;
                        bling(j, a);
                    }
                }
            }
            actiond(mi + 4, ma, i, a, "数据:源", "数据:目的");
            mem[mi][ma].status = 1;
            mem[mi][ma].list[i] = 1;
            cache[i][a].status = 1;
            cache[i][a].addrOfMem = addr;
            bling(mi + 4, ma);
            bling(i, a);
        }

        private void Simulate(int i)
        {
            // 计算相联度
            int connect = 1;
            for (int ii = 0, last = comboBox5.SelectedIndex; ii < last; ii++)
                connect = connect * 2;
            int addr;
            // 处理异常
            if (Int32.TryParse(textBox[i].Text, out addr) == false)
            {
                MessageBox.Show("wrong type");
                return;
            }
            if (addr < 0 || addr >= 32)
            {
                MessageBox.Show("out of range");
                return;
            }
            // 找到是第几个mem和mem中的地址
            int mem_index = addr / 8;
            int mem_addr = addr % 8;
            // 读或写
            int rw = comboBox[i].SelectedIndex;
            // 找到是哪块cache
            int cache_addr = get_cache_addr(i, addr, connect);
            //命中
            if (cache[i][cache_addr].status > 0 && cache[i][cache_addr].addrOfMem == addr)
            {
                //读
                if (rw == 0)
                {
                    actions(i, cache_addr, "读命中");
                    bling(i, cache_addr);
                }
                //写
                else
                {
                    //modified
                    if (cache[i][cache_addr].status == 1)
                    {
                        actions(i, cache_addr, "写命中");
                        bling(i, cache_addr);
                    }
                    //shared
                    else
                    {
                        actiond(i, cache_addr, mem_index + 4, mem_addr, "写命中:源", "写命中:目的");
                        for (int j = 0; j < 4; j++)
                        {
                            if (mem[mem_index][mem_addr].list[j] > 0 && j != i)
                            {
                                actiond(mem_index + 4, mem_addr, j, cache_addr, "作废:源", "作废:目的");
                                mem[mem_index][mem_addr].list[j] = 0;
                                actions(j, cache_addr, "作废");
                                cache[j][cache_addr].status = 0;
                                bling(j, cache_addr);
                            }
                        }
                        mem[mem_index][mem_addr].status = 1;
                        cache[i][cache_addr].status = 1;
                        bling(mem_index + 4, mem_addr);
                        bling(i, cache_addr);
                    }
                }
            }
            //不命中
            else
            {
                //读
                if (rw == 0)
                {
                    //invalid
                    if (cache[i][cache_addr].status == 0)
                    {
                        readmiss(i, cache_addr, mem_index, mem_addr, addr);
                    }
                    //modified
                    else if (cache[i][cache_addr].status == 1)
                    {
                        int ind = cache[i][cache_addr].addrOfMem / 8;
                        int add = cache[i][cache_addr].addrOfMem % 8;
                        actiond(i, cache_addr, ind + 4, add, "写回&修改共享集:源", "写回&修改共享集:目的");
                        mem[ind][add].list[i] = 0;
                        mem[ind][add].status = 0;
                        bling(ind + 4, add);
                        readmiss(i, cache_addr, mem_index, mem_addr, addr);
                    }
                    //shared
                    else
                    {
                        int ind = cache[i][cache_addr].addrOfMem / 8;
                        int add = cache[i][cache_addr].addrOfMem % 8;
                        actiond(i, cache_addr, ind + 4, add, "修改共享集:源", "修改共享集:目的");
                        mem[ind][add].list[i] = 0;
                        int ct = 0;
                        for (int j = 0; j < 4; j++) if (mem[ind][add].list[j] > 0) ct++;
                        if (ct > 0) mem[ind][add].status = 2;
                        else mem[ind][add].status = 0;
                        bling(ind + 4, add);
                        readmiss(i, cache_addr, mem_index, mem_addr, addr);
                    }
                }
                //写
                else
                {
                    //invalid
                    if (cache[i][cache_addr].status == 0)
                    {
                        writemiss(i, cache_addr, mem_index, mem_addr, addr);
                    }
                    //modified
                    else if (cache[i][cache_addr].status == 1)
                    {
                        int ind = cache[i][cache_addr].addrOfMem / 8;
                        int add = cache[i][cache_addr].addrOfMem % 8;
                        actiond(i, cache_addr, ind + 4, add, "写回&修改共享集:源", "写回&修改共享集:目的");
                        mem[ind][add].list[i] = 0;
                        mem[ind][add].status = 0;
                        bling(ind + 4, add);
                        writemiss(i, cache_addr, mem_index, mem_addr, addr);
                    }
                    //shared
                    else
                    {
                        int ind = cache[i][cache_addr].addrOfMem / 8;
                        int add = cache[i][cache_addr].addrOfMem % 8;
                        actiond(i, cache_addr, ind + 4, add, "修改共享集:源", "修改共享集:目的");
                        mem[ind][add].list[i] = 0;
                        int ct = 0;
                        for (int j = 0; j < 4; j++) if (mem[ind][add].list[j] > 0) ct++;
                        if (ct > 0) mem[ind][add].status = 2;
                        else mem[ind][add].status = 0;
                        bling(ind + 4, add);
                        writemiss(i, cache_addr, mem_index, mem_addr, addr);
                    }
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Simulate(0);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Simulate(1);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Simulate(2);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Simulate(3);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }
        
        // reset
        private void button1_Click(object sender, EventArgs e)
        {
            int i, j, k;
            comboBox5.SelectedIndex = 0;
            dataGridView[0] = this.dataGridView1;
            dataGridView[1] = this.dataGridView2;
            dataGridView[2] = this.dataGridView3;
            dataGridView[3] = this.dataGridView4;
            dataGridView[4] = this.dataGridView5;
            dataGridView[5] = this.dataGridView6;
            dataGridView[6] = this.dataGridView7;
            dataGridView[7] = this.dataGridView8;
            textBox[0] = this.textBox1;
            textBox[1] = this.textBox2;
            textBox[2] = this.textBox3;
            textBox[3] = this.textBox4;
            comboBox[0] = this.comboBox1;
            comboBox[1] = this.comboBox2;
            comboBox[2] = this.comboBox3;
            comboBox[3] = this.comboBox4;

            for (i = 0; i < 4; i++)
            {
                dataGridView[i].AutoResizeRows(DataGridViewAutoSizeRowsMode.AllCells);
                dataGridView[i].AllowUserToAddRows = false;
                dataGridView[i].Rows[0].Cells[1].Value = "";
                dataGridView[i].Rows[1].Cells[1].Value = "";
                dataGridView[i].Rows[2].Cells[1].Value = "";
                dataGridView[i].Rows[3].Cells[1].Value = "";
                dataGridView[i].Rows[0].Cells[2].Value = "";
                dataGridView[i].Rows[1].Cells[2].Value = "";
                dataGridView[i].Rows[2].Cells[2].Value = "";
                dataGridView[i].Rows[3].Cells[2].Value = "";

                dataGridView[i].Rows[0].Cells[1].Style.BackColor = invalid;
                dataGridView[i].Rows[1].Cells[1].Style.BackColor = invalid;
                dataGridView[i].Rows[2].Cells[1].Style.BackColor = invalid;
                dataGridView[i].Rows[3].Cells[1].Style.BackColor = invalid;
            }
            for (i = 4; i < 8; i++)
            {
                dataGridView[i].AllowUserToAddRows = false;
                for (j = 0; j < 8; j++)
                {
                    dataGridView[i].Rows[j].Cells[1].Value = "";
                    dataGridView[i].Rows[j].Cells[2].Style.BackColor = unbuffered;
                    dataGridView[i].Rows[j].Cells[2].Value = "";
                }
            }
            comboBox1.SelectedIndex = 0;
            comboBox2.SelectedIndex = 0;
            comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 0;
            textBox1.Text = "0";
            textBox2.Text = "0";
            textBox3.Text = "0";
            textBox4.Text = "0";

            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                {
                    cache[i][j].addrOfMem = -1;
                    cache[i][j].status = 0;
                }
            for (i = 0; i < 4; i++)
                for (j = 0; j < 8; j++)
                {
                    mem[i][j].status = 0;
                    for (k = 0; k < 4; k++)
                        mem[i][j].list[k] = 0;
                }
        }
    }
}
