//Room: /d/mingjiao/fangtang.c

inherit ROOM;
string* names = ({
        "/d/emei/obj/mala-doufu",
        "/d/emei/obj/bocai-fentiao",
        "/d/emei/obj/shanhu-baicai",
        "/d/emei/obj/liuli-qiezi",
        "/d/hangzhou/npc/obj/fish",
        "/d/hangzhou/npc/obj/pork",
        "/d/hangzhou/npc/obj/shrimp",
        "/d/hangzhou/npc/obj/geng",
        "/d/hangzhou/npc/obj/chicken",
        "/d/hangzhou/npc/obj/baozi",
});

void create()
{
        set("short","明教飯堂");
        set("long", @LONG
這裏便是明教的飯堂。擺滿了長長的餐桌和長凳，幾位年輕教眾
正來回忙碌着佈置。桌上擺了幾盆豆腐，花生，青菜以及大魚，大肉，
雞，酒等美味食。東邊的走廊通向廣場。
LONG );
        set("exits",([ /* sizeof() == 1 */
                "east" : __DIR__"square",
        ]));

        set("objects",([
                "/d/hangzhou/npc/obj/jiuping": 1,
                names[random(sizeof(names))]: 1,
                names[random(sizeof(names))]: 1,
                names[random(sizeof(names))]: 1,
                names[random(sizeof(names))]: 1,
                names[random(sizeof(names))]: 1,
        ]));
        setup();
        replace_program(ROOM);
}