inherit ROOM;

void create()
{
        set("short", "大廳");
        set("long", @LONG
這是白駝山莊的大廳，內部擺設極盡豪華，當中一張黑色檀木條
案，上面陳放著精美的花瓶和一些珍貴的瓷器，四壁掛滿名家的字畫，
非常之醒目。
LONG );
        set("valid_startroom", 1);
        set("exits", ([
                "north" : __DIR__"liangong",
                "southdown" : __DIR__"yuanzi",
        ]));
 
        set("objects",([
                CLASS_D("ouyang") + "/ouyangfeng" : 1,
                __DIR__"npc/yahuan" : 2,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();

        "/clone/board/baituo_b"->foo();
        replace_program(ROOM);
}