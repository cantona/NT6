// Room: /d/yueyang/dongtingmiao1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "洞庭廟主殿");
        set("long", @LONG
洞庭廟位於君山東北角秋月嶺的半山腰。主殿重檐歇山頂、青釉筒
瓦、雙弓形山牆，入口門廳塑東西二將把守殿堂。主殿正中是一尊面目
猙獰的黑臉大王柳毅像。柳毅被封王為洞庭王。龍王擔心柳毅這白麪書
生鎮不住水妖陸怪，便命錢塘君做了怪面具，讓柳毅白天戴着巡查湖岸，
晚上脱下怪面具，於是，柳毅便由白面書生變成了黑臉大王。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"xiaolu8",
                "east"  : __DIR__"yinyangting",
                "west"  : __DIR__"taijiting",
                "north" : __DIR__"dongtingmiao2",
        ]));
        set("coor/x", -1660);
        set("coor/y", 2350);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}