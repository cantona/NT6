// /yubifeng/dating.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "大廳");
        set("long", @long
大廳看來極大，四角各生著一盆大炭火。廳上居中掛著一副木板對
聯，寫著廿二個大字：“不來遼東大言天下無敵手，邂逅冀北方信世間
有英雄”。上款是“希孟仁兄正之”，下款是“妄人苗人鳳深慚昔年狂
言醉後塗鴉”。
long );
        set("exits", ([
                "south" : __DIR__"changlang",
                "west"  : __DIR__"zoulang1",
                "east"  : __DIR__"zoulang2",
        ]));
        set("objects", ([
                __DIR__"npc/duximeng" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6120);
        set("coor/y", 5180);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}