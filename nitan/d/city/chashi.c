// By haiyan

inherit ROOM;

int is_chat_room() {return 1;}
void create()
{
        set("short", "茶室");
        set("long", @LONG
這裏是春來茶館的二樓雅座。你站在樓上眺望，只見揚州大街上
人羣熙攘，小販子的叫賣聲摻雜着討價聲此起彼伏。許多穿着考究的
公子哥兒頻繁進出於對面一間裝飾華麗的大院，不時傳來陣陣打情罵
俏的聲音。江湖上許多事都可以在這裏打聽到。
LONG );

        set("exits", ([
                "down" : "/d/city/chaguan",
        ]));

        set("no_fight", "1");
        setup();
        "/clone/board/player_b"->foo();
}
