//Room: qunyums.c

inherit ROOM;

void create()
{
        set("short", "羣玉樓密室");
        set("long", @LONG
屋子裏面佈置得簡單而富有情趣。房間很寬敞，懸掛着幾盆花花
草草，紅綠相間，疏密有致，令人賞心悦目。屋子裏一個十來歲的小
姑娘正哭個不停，旁邊站了四個打手。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "south" : "/d/changan/qunyuys8",
        ]));
        set("objects", ([
                "/d/changan/npc/dashou" : 4,
                "/d/changan/npc/xiangxiang": 1,
                "/d/changan/npc/huangyi": 1,   
        ]) );

        setup();
        replace_program(ROOM);
}