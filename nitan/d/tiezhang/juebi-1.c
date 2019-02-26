inherit ROOM;

void create()
{
        set("short", "峭壁");
        set("long", @LONG
你走到這裏，發現前面已經沒有路了。你面前是一座立陡的山峯，高聳
入雲，看不到盡頭。石壁上生長着很多松樹，疾風吹來，沙沙作響。
LONG    );
        set("exits", ([
                "southwest" : __DIR__"shangu-2",
                "northup" : __DIR__"szfeng",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");
        setup();
}