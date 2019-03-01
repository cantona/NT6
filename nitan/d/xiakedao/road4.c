// road4.c 山路
// by Xiang

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一條巖石嶙峋的山道上，左臨深澗，澗水緩急，激石有
聲。右邊是懸崖，抬頭隱約可見籠罩在雲霧中的山峰，一路沿著山
潼漸行漸高。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup" : __DIR__"pubu",
                "northdown" : __DIR__"road3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -22050);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}