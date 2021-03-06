inherit ROOM;

void create()
{
        set("short", "郭府大廳");
        set("long", @LONG
這裏是郭府的客廳。廳雖不大，卻佈置的挺雅緻。東壁懸
掛着四幅屏條，繪的是梅蘭菊竹四種花卉；西壁懸掛的是春夏
秋冬。內廳居中的是一張八仙桌。桌上端放着一套茶具，兩旁
擺放着四張檀香椅，顯得極為古樸。廳角各擺放着一盆牡丹花
似乎給這裏帶來一絲暖意。北壁內牆神龕供奉岳飛的畫像，上
面是一條橫幅，上書「還我河山」。往北走是個長廊，一直通
向館主的卧室。
LONG);
        set("no_fight", 1);

        set("objects", ([
                "/quest/quest5/guo.c" : 1,
        ]));
        set("exits", ([
               "south" : __DIR__"guofu_dayuan2",
               "north" : __DIR__"guofu_lang5",
               "west" : __DIR__"guofu_shilu-2",
               "east" : __DIR__"guofu_shilu-1",
        ]));

        setup();
        //"/d/wuguan/npc/guojing"->come_here();
}