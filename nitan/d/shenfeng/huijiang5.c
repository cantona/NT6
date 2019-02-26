inherit ROOM;

void create()
{
        set("short", "綠洲");
        set("long", @LONG
在沙漠的盡頭出現了一個綠洲。這兒是南疆難得一見的草
原。草原上的夜晚，天很高、很藍，星星很亮，青草和小花散
播著芳香。隱隱約約隨風聲飄來天鈴鳥的歌聲。這裏居住着哈
薩克人, 以放牧羊羣為生。灌木叢中有一眼坎兒井。井台上有
個木杯專供口渴的行人喝水。井邊是一塊瓜地。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                "west" : __DIR__"huijiang3",
                "north" : __DIR__"huijiang7",
                "east" : __DIR__"lake4",
        ]));
        set("objects", ([
                    __DIR__"npc/su" : 1,
                "/clone/quarry/yang" : 2,
        ]));
        set("quarrys", ([
                "yang"  : 50000,
                "lang"  : 30000,
                "ying"  : 10000,
        ]));
        setup();
        replace_program(ROOM);
}