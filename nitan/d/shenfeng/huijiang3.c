inherit ROOM;

void create()
{
        set("short", "南疆小鎮");
        set("long", @LONG
從草原上南下，便接近南疆沙漠了。這兒氣候逐漸幹燥熱
浪時而從沙漠裡湧來。沙漠裡還走來駱駝商隊，在這兒休息分
發貨物。于是商舖林立人來人往十分熱鬧。西面是一小院。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                    "northup" : __DIR__"huijiang2",
                "south" : __DIR__"huijiang6",
                    "west" : __DIR__"huijiang4",
                    "east" : __DIR__"huijiang5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}