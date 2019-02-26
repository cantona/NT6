// Room: /d/wuyi/tianyoufeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "天遊峯");
        set("long", @LONG
天遊峯位於六曲之北，壁立萬仞，高聳羣峯之上。每每雨後天晴抑
或晨曦初露之時，山谷瀰漫着白茫茫的煙雲，氣象萬千。登巔頂，望雲
海，變幻莫測，宛如置身蓬萊仙境，猶如遨遊玉闕天宮，故名天遊。徐
霞客曰：“其不臨溪而能盡九曲之勝，此峯固應第一也。”然也。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "up"        : __DIR__"tianyouguan",
                "eastdown"  : __DIR__"tianyoupath1",
                "northdown" : __DIR__"tianyoupath2",
                "northeast" : __DIR__"xianyutan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -4970);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
