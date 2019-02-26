// road5.c 小徑

inherit ROOM;

void create()
{
        object ob;

        set("short", "小徑");
        set("long", @LONG
這是一條蜿蜒的小徑，曲曲折折通往山裏。路旁有一間小磚房，煙筒
裏面時不時冒出一股股黑煙，聞起來有些難受，你一時忍不住想打兩個噴
嚏。屋裏面傳來陣陣的敲打聲音，看來這裏是給村民們打造菜刀、犁頭的
鐵匠鋪。
LONG );

        set("exits", ([
                "west"  : __DIR__"road4",
                "enter" : __DIR__"xiaowu",
        ]));
        set("outdoors", "suzhou");
        set("coor/x", 900);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}