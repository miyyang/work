import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;
import javax.swing.border.EtchedBorder;

import java.io.File;
import java.lang.*;
import java.util.*;


public class CCacheSim extends JFrame implements ActionListener {

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         variables                                       /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    private JPanel panelTop, panelLeft, panelRight, panelBottom;
    private JButton execStepBtn, execAllBtn, fileBotton;
    private JComboBox<String> csBox, bsBox, wayBox, replaceBox, prefetchBox, writeBox, allocBox;
    private JComboBox<String> icsBox, dcsBox;
    private JFileChooser fileChooser;

    private JLabel labelTop,labelLeft,bottomLabel,fileLabel,fileAddrBtn, stepLabel1, stepLabel2,
            csLabel, bsLabel, wayLabel, replaceLabel, prefetchLabel, writeLabel, allocLabel;

    private JLabel icsLabel, dcsLabel;
    private JLabel resultTagLabel[][];
    private JLabel resultDataLabel[][];
    private JLabel accessTypeTagLabel, addressTagLabel, blockNumberTagLabel, tagTagLabel, indexTagLabel, ins_offsetessTagLabel, hitTagLabel;
    private JLabel accessTypeDataLabel, addressDataLabel, blockNumberDataLabel, tagDataLabel, indexDataLabel, ins_offsetessDataLabel, hitDataLabel;
    private JRadioButton unifiedata_CacheButton, separateCacheButton;

    private String cachesize[] = { "2KB", "8KB", "32KB", "128KB", "512KB", "2MB" };
    private String half_cachesize[] = { "1KB", "4KB", "16KB", "64KB", "256KB", "1MB" };
    private String blocksize[] = { "16B", "32B", "64B", "128B", "256B" };
    private String way[] = { "直接映象", "2路", "4路", "8路", "16路", "32路" };
    private String replace[] = { "LRU", "FIFO", "RAND" };
    private String pref[] = { "不预取", "不命中预取" };
    private String write[] = { "写回法", "写直达法" };
    private String alloc[] = { "按写分配", "不按写分配" };
    private String typename[] = { "读数据", "写数据", "读指令" };
    private String hitname[] = {"不命中", "命中" };

    private String resultlabel[][] = {
            {"访问总次数:", "不命中次数:", "不命中率:"},
            {"读指令次数:", "不命中次数:", "不命中率:"},
            {"读数据次数:", "不命中次数:", "不命中率:"},
            {"写数据次数:", "不命中次数:", "不命中率:"}
    };

    private File file;

    // user configuration
    private int csIndex, bsIndex, wayIndex, replaceIndex, prefetchIndex, writeIndex, allocIndex, icsIndex, dcsIndex, cacheType = 0;
    private int now_csIndex, now_bsIndex, now_wayIndex, now_replaceIndex, now_prefetchIndex, now_writeIndex, now_allocIndex, now_icsIndex, now_dcsIndex, now_cacheType = 0;

    private Instruction instructions[];
    private int max_ins_size = 20000000;
    private int ins_size;
    private int ip;

    private Cache united_Cache, ins_Cache, data_Cache;

    private int read_data_miss, read_data_hit;
    private int read_ins_miss, read_ins_hit;
    private int write_data_miss, write_data_hit;
    private int write_mem_total;

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         instructions pre_processing                     /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    private class Instruction {
        int ins_kind;
        String hex_address;
        String bin_address;
        int tag;
        int index;
        int ins_block;
        int ins_offset;

        public Instruction(int ins_kind, String hex_address) {
            this.ins_kind = ins_kind;
            this.hex_address = hex_address;
            this.bin_address = hex2bin(hex_address);
            int addr_len = 32;

            //########################################################################
            //###### address form = [ins_block ins_offset] = [tag index offset] ######
            //########################################################################

            if (now_cacheType == 0 && united_Cache != null) {
                int temp = addr_len - united_Cache.blockOffset;
                this.tag = Integer.parseInt(bin_address.substring(0, temp - united_Cache.groupOffset), 2);
                this.index = Integer.parseInt(bin_address.substring(temp - united_Cache.groupOffset, temp), 2);
                this.ins_block = Integer.parseInt(bin_address.substring(0, temp), 2);
                this.ins_offset = Integer.parseInt(bin_address.substring(temp), 2);
            }
            else if (now_cacheType == 1 && ins_Cache != null && data_Cache != null) {
                if (ins_kind == 0 || ins_kind == 1) {
                    int temp = addr_len - data_Cache.blockOffset;
                    this.tag = Integer.parseInt(bin_address.substring(0, temp - data_Cache.groupOffset), 2);
                    this.index = Integer.parseInt(bin_address.substring(temp - data_Cache.groupOffset, temp), 2);
                    this.ins_block = Integer.parseInt(bin_address.substring(0, temp), 2);
                    this.ins_offset = Integer.parseInt(bin_address.substring(temp), 2);
                } else if (ins_kind == 2) {
                    int temp = addr_len - ins_Cache.blockOffset;
                    this.tag = Integer.parseInt(bin_address.substring(0, temp - ins_Cache.groupOffset), 2);
                    this.index = Integer.parseInt(bin_address.substring(temp - ins_Cache.groupOffset, temp), 2);
                    this.ins_block = Integer.parseInt(bin_address.substring(0, temp), 2);
                    this.ins_offset = Integer.parseInt(bin_address.substring(temp), 2);
                }
            }
        }

    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         cache_block class                               /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    private class CacheBlock {
        int tag;
        boolean dirty;
        long count;
        long time;

        public CacheBlock(int tag) {
            this.tag = tag;
            this.dirty = false;
            this.count = -1L;
            this.time = -1L;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         cache class                                     /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    private class Cache {

        private CacheBlock cache[][];
        private int 	cacheSize;
        private int 	blockSize;
        private int 	blockNum;
        private int 	blockOffset;
        private int 	blockNumInAGroup;
        private int 	groupNum;
        private int 	groupOffset;

        private long FIFO_order[];
        private long LRU_order[];

        public Cache(int cacheSize, int blockSize) {
            this.cacheSize = cacheSize;
            this.blockSize = blockSize;

            blockNum = cacheSize / blockSize;
            blockOffset = log2(blockSize);
            blockNumInAGroup = pow(2, now_wayIndex);
            groupNum = blockNum / blockNumInAGroup;
            groupOffset = log2(groupNum);

            cache = new CacheBlock[groupNum][blockNumInAGroup];

            for (int i = 0; i < groupNum; i++)
                for (int j = 0; j < blockNumInAGroup; j++)
                    // tag as available
                    cache[i][j] = new CacheBlock(-1);
            FIFO_order = new long[groupNum];
            LRU_order = new long[groupNum];
        }

        public boolean read(int tag, int index, int ins_offset) {
            // try to search for the right block
            for (int i = 0; i < blockNumInAGroup; i++)
                if (cache[index][i].tag == tag) {
                    // fix a problem here. can't use counting.
                    cache[index][i].count = LRU_order[index];
                    LRU_order[index]++;
                    return true;
                }
            return false;
        }

        public boolean write(int tag, int index, int ins_offset) {
            // try to search for the right block
            for (int i = 0; i < blockNumInAGroup; i++)
                if (cache[index][i].tag == tag) {
                    cache[index][i].count = LRU_order[index];
                    LRU_order[index]++;
                    cache[index][i].dirty = true;
                    if (now_writeIndex == 1) {
                        // if it's write through, write it through to the memory now
                        write_mem_total++;
                        cache[index][i].dirty = false;
                    }
                    return true;
                }
            return false;
        }

        public void prefetch(int nextins_block) {
            int nextTag = nextins_block / pow(2, groupOffset + blockOffset);
            int nextIndex = nextins_block / pow(2, blockOffset) % pow(2, groupOffset);
            replaceCacheBlock(nextTag, nextIndex);
        }

        public void replaceCacheBlock(int tag, int index) {
            if (now_replaceIndex == 0) {
                int lruBlock = 0;
                for (int i = 1; i < blockNumInAGroup; i++)
                    if (cache[index][lruBlock].count > cache[index][i].count)
                        lruBlock = i;
                loadToCache(tag, index, lruBlock);
            }
            else if (now_replaceIndex == 1) {
                int fifoBlock = 0;
                for (int i = 1; i < blockNumInAGroup; i++)
                    if (cache[index][fifoBlock].time > cache[index][i].time)
                        fifoBlock = i;
                loadToCache(tag, index, fifoBlock);
            }
            else if (now_replaceIndex == 2)
                loadToCache(tag, index, random(0, blockNumInAGroup));
        }

        private void loadToCache(int tag, int index, int groupAddr) {
            if (now_writeIndex == 0 && cache[index][groupAddr].dirty)
                write_mem_total++;
            cache[index][groupAddr].tag = tag;
            cache[index][groupAddr].count = LRU_order[index];
            LRU_order[index]++;
            cache[index][groupAddr].dirty = false;
            cache[index][groupAddr].time = FIFO_order[index];
            FIFO_order[index]++;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         cache initialization                            /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    public CCacheSim(){
        super("Cache Simulator");
        fileChooser = new JFileChooser();
        fileChooser.setFileFilter(new DinFileFilter());
        draw();
    }

    private void initCache() {
        read_data_hit = read_data_miss = 0;
        read_ins_hit = read_ins_miss = 0;
        write_data_miss = write_data_hit = 0;
        write_mem_total = 0;

        if (now_cacheType == 0) {
            united_Cache = new Cache(2 * 1024 * pow(4, now_csIndex), 16 * pow(2, now_bsIndex));
            ins_Cache = null;
            data_Cache = null;

        }
        else if (now_cacheType == 1) {
            united_Cache = null;
            ins_Cache = new Cache(1 * 1024 * pow(4, now_icsIndex), 16 * pow(2, now_bsIndex));
            data_Cache = new Cache(1 * 1024 * pow(4, now_dcsIndex), 16 * pow(2, now_bsIndex));
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         file manipulation                               /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    private void readFile() {
        try {
            Scanner s = new Scanner(file);
            instructions = new Instruction[max_ins_size];
            ins_size = 0;
            ip = 0;

            while(s.hasNextLine()) {
                String line = s.nextLine();
                String[] items = line.split(" ");
                instructions[ins_size] = new Instruction(Integer.parseInt(items[0].trim()), items[1].trim());
                ins_size++;
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    private class DinFileFilter extends FileFilter{
        public boolean accept(File f) {
            if (f.isDirectory()) return true;
            String name = f.getName();
            return name.endsWith(".din");
        }
        public String getDescription() {
            return ".din";
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         execution                                       /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == execAllBtn) {
            simExecAll();
        }
        if (e.getSource() == execStepBtn) {
            simExecStep(true);
        }
        if (e.getSource() == fileBotton){
            int fileOver = fileChooser.showOpenDialog(null);
            if (fileOver == 0) {
                String path = fileChooser.getSelectedFile().getAbsolutePath();
                fileAddrBtn.setText(path);
                file = new File(path);
                now_cacheType = cacheType;
                now_csIndex = csIndex;
                now_icsIndex = icsIndex;
                now_dcsIndex = dcsIndex;
                now_bsIndex = bsIndex;
                now_wayIndex = wayIndex;
                now_replaceIndex = replaceIndex;
                now_prefetchIndex = prefetchIndex;
                now_writeIndex = writeIndex;
                now_allocIndex = allocIndex;

                initCache();
                readFile();
                reloadUI();
            }
        }
    }

    private void simExecStep(boolean oneStepExec) {
        ip %= ins_size;
        if (ip == 0) {
            initCache();
            reloadUI();
        }
        int ins_kind = instructions[ip].ins_kind;
        int index = instructions[ip].index;
        int tag = instructions[ip].tag;
        int ins_offset = instructions[ip].ins_offset;

        boolean isHit = false;
        if (now_cacheType == 0) {
            if (ins_kind == 0) {
                isHit = united_Cache.read(tag, index, ins_offset);
                if (isHit)
                    read_data_hit++;
                else {
                    read_data_miss++;
                    united_Cache.replaceCacheBlock(tag, index);
                }
            }
            else if (ins_kind == 1) {
                isHit = united_Cache.write(tag, index, ins_offset);
                if (isHit)
                    write_data_hit++;
                else {
                    write_data_miss++;
                    if (now_allocIndex == 0) {
                        united_Cache.replaceCacheBlock(tag, index);
                        united_Cache.write(tag, index, ins_offset);
                    } else if (now_allocIndex == 1)
                        write_mem_total++;
                }
            }
            else if (ins_kind == 2) {
                isHit = united_Cache.read(tag, index, ins_offset);
                if (isHit)
                    read_ins_hit++;
                else {
                    read_ins_miss++;
                    united_Cache.replaceCacheBlock(tag, index);
                    if (now_prefetchIndex == 1)
                        united_Cache.prefetch(instructions[ip].ins_block + 1);
                }
            }
        }
        else if (now_cacheType == 1) {
            if (ins_kind == 0) {
                isHit = data_Cache.read(tag, index, ins_offset);
                if (isHit)
                    read_data_hit++;
                else {
                    read_data_miss++;
                    data_Cache.replaceCacheBlock(tag, index);
                }
            }
            else if (ins_kind == 1) {
                isHit = data_Cache.write(tag, index, ins_offset);
                if (isHit)
                    write_data_hit++;
                else {
                    write_data_miss++;
                    if (now_allocIndex == 0) {
                        data_Cache.replaceCacheBlock(tag, index);
                        data_Cache.write(tag, index, ins_offset);
                    }
                    else if (now_allocIndex == 1)
                        write_mem_total++;
                }
            }
            else if (ins_kind == 2) {
                isHit = ins_Cache.read(tag, index, ins_offset);
                if (isHit)
                    read_ins_hit++;
                else {
                    read_ins_miss++;
                    ins_Cache.replaceCacheBlock(tag, index);
                    if (now_prefetchIndex == 1)
                        ins_Cache.prefetch(instructions[ip].ins_block + 1);
                }
            }
        }

        if (oneStepExec || ip == ins_size - 1)
            statisticUIUpdate(instructions[ip], isHit);

        ip++;
    }

    private void simExecAll() {
        while (ip < ins_size) {
            simExecStep(false);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         util function                                   /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    private int pow(int x, int p) {
        return (int)Math.pow(x, p);
    }

    private int log2(int x) {
        return (int)(Math.log(x) / Math.log(2));
    }

    private int random(int x, int y) {
        return (int)Math.random() * (y - x) + x;
    }

    private String hex2bin(String hex_address) {
        StringBuffer temp = new StringBuffer();
        int i;
        String[] mapping =
                {"0000","0001","0010","0011","0100","0101","0110","0111",
                        "1000","1001","1010","1011","1100","1101","1110","1111"};
        for (i = 0; i < 8 - hex_address.length(); i++) {
            temp.append(mapping[0]);
        }
        for (i = 0; i < hex_address.length(); i++) {
            int ind = hex_address.charAt(i) - '0';
            if (ind > 9)
                ind = hex_address.charAt(i) - 'a' + 10;
            temp.append(mapping[ind]);
        }
        return temp.toString();
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         user interface                                  /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    private void unifiedata_CacheEnabled(boolean enabled) {
        unifiedata_CacheButton.setSelected(enabled);
        csLabel.setEnabled(enabled);
        csBox.setEnabled(enabled);
    }

    private void separateCacheEnabled(boolean enabled) {
        separateCacheButton.setSelected(enabled);
        icsLabel.setEnabled(enabled);
        dcsLabel.setEnabled(enabled);
        icsBox.setEnabled(enabled);
        dcsBox.setEnabled(enabled);
    }

    private void draw() {
        setLayout(new BorderLayout(5,5));
        panelTop = new JPanel();
        panelLeft = new JPanel();
        panelRight = new JPanel();
        panelBottom = new JPanel();
        panelTop.setPreferredSize(new Dimension(800, 50));
        panelLeft.setPreferredSize(new Dimension(300, 450));
        panelRight.setPreferredSize(new Dimension(500, 450));
        panelBottom.setPreferredSize(new Dimension(800, 100));
        panelTop.setBorder(new EtchedBorder(EtchedBorder.RAISED));
        panelLeft.setBorder(new EtchedBorder(EtchedBorder.RAISED));
        panelRight.setBorder(new EtchedBorder(EtchedBorder.RAISED));
        panelBottom.setBorder(new EtchedBorder(EtchedBorder.RAISED));

        labelTop = new JLabel("Cache Simulator");
        labelTop.setAlignmentX(CENTER_ALIGNMENT);
        panelTop.add(labelTop);


        labelLeft = new JLabel("Cache设置");
        labelLeft.setPreferredSize(new Dimension(300, 40));

        csLabel = new JLabel("Cache");
        csLabel.setPreferredSize(new Dimension(80, 30));
        csBox = new JComboBox<String>(cachesize);
        csBox.setPreferredSize(new Dimension(90, 30));
        csBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                csIndex = csBox.getSelectedIndex();
            }
        });

        unifiedata_CacheButton = new JRadioButton("Unified_Cache:", true);
        unifiedata_CacheButton.setPreferredSize(new Dimension(100, 30));
        unifiedata_CacheButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                separateCacheEnabled(false);
                unifiedata_CacheEnabled(true);
                cacheType = 0;
            }
        });

        separateCacheButton = new JRadioButton("Seperated_Cache:");
        separateCacheButton.setPreferredSize(new Dimension(100, 30));
        separateCacheButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                separateCacheEnabled(true);
                unifiedata_CacheEnabled(false);
                cacheType = 1;
            }
        });

        icsLabel = new JLabel("instructions Cache");
        icsLabel.setPreferredSize(new Dimension(80, 30));

        dcsLabel = new JLabel("data Cache");
        dcsLabel.setPreferredSize(new Dimension(80, 30));

        JLabel emptyLabel = new JLabel("");
        emptyLabel.setPreferredSize(new Dimension(100, 30));

        icsBox = new JComboBox<String>(half_cachesize);
        icsBox.setPreferredSize(new Dimension(90, 30));
        icsBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                icsIndex = icsBox.getSelectedIndex();
            }
        });

        dcsBox = new JComboBox<String>(half_cachesize);
        dcsBox.setPreferredSize(new Dimension(90, 30));
        dcsBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                dcsIndex = dcsBox.getSelectedIndex();
            }
        });

        separateCacheEnabled(false);
        unifiedata_CacheEnabled(true);

        bsLabel = new JLabel("块大小");
        bsLabel.setPreferredSize(new Dimension(120, 30));
        bsBox = new JComboBox<String>(blocksize);
        bsBox.setPreferredSize(new Dimension(160, 30));
        bsBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                bsIndex = bsBox.getSelectedIndex();
            }
        });

        wayLabel = new JLabel("相联度");
        wayLabel.setPreferredSize(new Dimension(120, 30));
        wayBox = new JComboBox<String>(way);
        wayBox.setPreferredSize(new Dimension(160, 30));
        wayBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                wayIndex = wayBox.getSelectedIndex();
            }
        });

        replaceLabel = new JLabel("替换策略");
        replaceLabel.setPreferredSize(new Dimension(120, 30));
        replaceBox = new JComboBox<String>(replace);
        replaceBox.setPreferredSize(new Dimension(160, 30));
        replaceBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                replaceIndex = replaceBox.getSelectedIndex();
            }
        });

        prefetchLabel = new JLabel("预取策略");
        prefetchLabel.setPreferredSize(new Dimension(120, 30));
        prefetchBox = new JComboBox<String>(pref);
        prefetchBox.setPreferredSize(new Dimension(160, 30));
        prefetchBox.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e){
                prefetchIndex = prefetchBox.getSelectedIndex();
            }
        });

        writeLabel = new JLabel("写策略");
        writeLabel.setPreferredSize(new Dimension(120, 30));
        writeBox = new JComboBox<String>(write);
        writeBox.setPreferredSize(new Dimension(160, 30));
        writeBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                writeIndex = writeBox.getSelectedIndex();
            }
        });

        allocLabel = new JLabel("写不命中调块策略");
        allocLabel.setPreferredSize(new Dimension(120, 30));
        allocBox = new JComboBox<String>(alloc);
        allocBox.setPreferredSize(new Dimension(160, 30));
        allocBox.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                allocIndex = allocBox.getSelectedIndex();
            }
        });

        fileLabel = new JLabel("选择指令流文件");
        fileLabel.setPreferredSize(new Dimension(120, 30));
        fileAddrBtn = new JLabel();
        fileAddrBtn.setPreferredSize(new Dimension(210,30));
        fileAddrBtn.setBorder(new EtchedBorder(EtchedBorder.RAISED));
        fileBotton = new JButton("浏览");
        fileBotton.setPreferredSize(new Dimension(70,30));
        fileBotton.addActionListener(this);

        panelLeft.add(labelLeft);

        panelLeft.add(unifiedata_CacheButton);
        panelLeft.add(csLabel);
        panelLeft.add(csBox);

        panelLeft.add(separateCacheButton);
        panelLeft.add(icsLabel);
        panelLeft.add(icsBox);
        panelLeft.add(emptyLabel);
        panelLeft.add(dcsLabel);
        panelLeft.add(dcsBox);

        panelLeft.add(bsLabel);
        panelLeft.add(bsBox);
        panelLeft.add(wayLabel);
        panelLeft.add(wayBox);
        panelLeft.add(replaceLabel);
        panelLeft.add(replaceBox);
        panelLeft.add(prefetchLabel);
        panelLeft.add(prefetchBox);
        panelLeft.add(writeLabel);
        panelLeft.add(writeBox);
        panelLeft.add(allocLabel);
        panelLeft.add(allocBox);
        panelLeft.add(fileLabel);
        panelLeft.add(fileAddrBtn);
        panelLeft.add(fileBotton);

        resultTagLabel = new JLabel[4][3];
        resultDataLabel = new JLabel[4][3];

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                resultTagLabel[i][j] = new JLabel(resultlabel[i][j]);
                resultTagLabel[i][j].setPreferredSize(new Dimension(70, 40));

                if (j != 2) {
                    resultDataLabel[i][j] = new JLabel("0");
                } else {
                    resultDataLabel[i][j] = new JLabel("0.00%");
                }

                resultDataLabel[i][j].setPreferredSize(new Dimension(83, 40));

                panelRight.add(resultTagLabel[i][j]);
                panelRight.add(resultDataLabel[i][j]);
            }
        }

        accessTypeTagLabel = new JLabel("类型:");
        addressTagLabel = new JLabel("地址:");
        blockNumberTagLabel = new JLabel("块号:");
        tagTagLabel = new JLabel("Tag:");
        indexTagLabel = new JLabel("组索引:");
        ins_offsetessTagLabel = new JLabel("块内偏移:");
        hitTagLabel = new JLabel("hit/miss:");

        accessTypeDataLabel = new JLabel("???");
        addressDataLabel = new JLabel("???");
        blockNumberDataLabel = new JLabel("???");
        tagDataLabel = new JLabel("???");
        indexDataLabel = new JLabel("???");
        ins_offsetessDataLabel = new JLabel("???");
        hitDataLabel = new JLabel("???");

        accessTypeTagLabel.setPreferredSize(new Dimension(80, 40));
        accessTypeDataLabel.setPreferredSize(new Dimension(80, 40));
        addressTagLabel.setPreferredSize(new Dimension(80, 40));
        addressDataLabel.setPreferredSize(new Dimension(200, 40));
        panelRight.add(accessTypeTagLabel);
        panelRight.add(accessTypeDataLabel);
        panelRight.add(addressTagLabel);
        panelRight.add(addressDataLabel);

        blockNumberTagLabel.setPreferredSize(new Dimension(80, 40));
        blockNumberDataLabel.setPreferredSize(new Dimension(200, 40));
        hitTagLabel.setPreferredSize(new Dimension(80, 40));
        hitDataLabel.setPreferredSize(new Dimension(80, 40));
        panelRight.add(blockNumberTagLabel);
        panelRight.add(blockNumberDataLabel);
        panelRight.add(hitTagLabel);
        panelRight.add(hitDataLabel);

        tagTagLabel.setPreferredSize(new Dimension(60, 40));
        tagDataLabel.setPreferredSize(new Dimension(70, 40));
        indexTagLabel.setPreferredSize(new Dimension(60, 40));
        indexDataLabel.setPreferredSize(new Dimension(70, 40));
        ins_offsetessTagLabel.setPreferredSize(new Dimension(60, 40));
        ins_offsetessDataLabel.setPreferredSize(new Dimension(100, 40));
        panelRight.add(tagTagLabel);
        panelRight.add(tagDataLabel);
        panelRight.add(indexTagLabel);
        panelRight.add(indexDataLabel);
        panelRight.add(ins_offsetessTagLabel);
        panelRight.add(ins_offsetessDataLabel);

        bottomLabel = new JLabel("control");
        bottomLabel.setPreferredSize(new Dimension(800, 30));
        execStepBtn = new JButton("步进");
        execStepBtn.setLocation(100, 30);
        execStepBtn.addActionListener(this);
        execAllBtn = new JButton("执行到底");
        execAllBtn.setLocation(300, 30);
        execAllBtn.addActionListener(this);

        panelBottom.add(bottomLabel);
        panelBottom.add(execStepBtn);
        panelBottom.add(execAllBtn);

        add("North", panelTop);
        add("West", panelLeft);
        add("Center", panelRight);
        add("South", panelBottom);
        setSize(820, 620);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void statisticUIUpdate(Instruction inst, boolean isHit) {

        int totalMissTime = read_ins_miss + read_data_miss + write_data_miss;
        int totalVisitTime = totalMissTime + read_ins_hit + read_data_hit + write_data_hit;

        resultDataLabel[0][0].setText(totalVisitTime + "");
        resultDataLabel[0][1].setText(totalMissTime + "");
        if (totalVisitTime > 0) {
            double missRate = ((double)totalMissTime / (double)totalVisitTime) * 100;
            resultDataLabel[0][2].setText(String.format("%.2f", missRate) + "%");
        }

        resultDataLabel[1][0].setText((read_ins_hit + read_ins_miss) + "");
        resultDataLabel[1][1].setText(read_ins_miss + "");
        if (read_ins_miss + read_ins_hit > 0) {
            double missRate = ((double)read_ins_miss/(double)(read_ins_miss + read_ins_hit)) * 100;
            resultDataLabel[1][2].setText(String.format("%.2f", missRate) + "%");
        }

        resultDataLabel[2][0].setText((read_data_hit + read_data_miss) + "");
        resultDataLabel[2][1].setText(read_data_miss + "");
        if (read_data_miss + read_data_hit > 0) {
            double missRate = ((double)read_data_miss/(double)(read_data_miss + read_data_hit)) * 100;
            resultDataLabel[2][2].setText(String.format("%.2f", missRate) + "%");
        }

        resultDataLabel[3][0].setText((write_data_hit + write_data_miss) + "");
        resultDataLabel[3][1].setText(write_data_miss + "");
        if (write_data_miss + write_data_hit > 0) {
            double missRate = ((double)write_data_miss/(double)(write_data_miss + write_data_hit)) * 100;
            resultDataLabel[3][2].setText(String.format("%.2f", missRate) + "%");
        }

        if (inst.ins_kind == 0) {
            accessTypeDataLabel.setText("读指令");
        } else if (inst.ins_kind == 1) {
            accessTypeDataLabel.setText("读数据");
        } else if (inst.ins_kind == 2) {
            accessTypeDataLabel.setText("写数据");
        } else {
            accessTypeDataLabel.setText("非法指令");
        }
        addressDataLabel.setText(inst.hex_address);
        blockNumberDataLabel.setText(inst.ins_block + "");
        tagDataLabel.setText(inst.tag + "");
        indexDataLabel.setText(inst.index + "");
        ins_offsetessDataLabel.setText(inst.ins_offset + "");

        if (isHit) {
            hitDataLabel.setText("命中");
        } else {
            hitDataLabel.setText("未命中");
        }
    }

    private void reloadUI() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                resultDataLabel[i][j].setText("0");
            }
            resultDataLabel[i][2].setText("0.00%");
        }

        accessTypeDataLabel.setText("???");
        addressDataLabel.setText("???");
        blockNumberDataLabel.setText("???");
        tagDataLabel.setText("???");
        indexDataLabel.setText("???");
        ins_offsetessDataLabel.setText("???");
        hitDataLabel.setText("???");
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////                                                                         /////
    /////                         entry function                                  /////
    /////                                                                         /////
    ///////////////////////////////////////////////////////////////////////////////////

    public static void main(String[] args) {
        new CCacheSim();
    }
}
