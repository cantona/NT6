inherit ROOM;

void create()
{
        set("short", "九老洞");
        set("long", @LONG
這就是峨嵋第一大洞，洞內深窈無比，神祕難測。你一走進來，
便發覺洞中叉叉洞多如迷宮，怪異莫測，似乎黝黑無底。洞裏隱隱傳
來雞犬鼓樂之聲，令人驚異間，忽有蝙蝠羣湧而至撲熄火炬。還是快
快離開吧。
LONG );
        set("objects", ([
           "/d/emei/npc/poorman" : 2,
           "/d/emei/npc/little_monkey" : 3,
                "/clone/quarry/fu" : 3,
        ]));
        set("exits", ([
                "south" : __DIR__"jiulaodong",
        ]));

        set("coor/x", -520);
        set("coor/y", -240);
        set("coor/z", 130);
        set("coor/x", -520);
        set("coor/y", -240);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}