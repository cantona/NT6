// Room: /guiyun/liangong.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裏是歸雲莊陸少莊主的練功房。由於陸少莊主乃少林旁支仙霞派
出身，所以房中佈置盡是為習練外門硬功之用，豎立着不少木樁和草靶。
西邊角上還有兩個大沙坑，天花板上吊着一隻大沙袋。
LONG );
        set("exits", ([
                "west"  : __DIR__"zoulang4",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren" : 3,
        ]));
        set("coor/x", 270);
        set("coor/y", -840);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}