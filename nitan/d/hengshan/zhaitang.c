// Last Modified by Sir on May. 22 2001
//Room: zhaitang.c 齋堂

inherit ROOM;
string* names = ({
        __DIR__"obj/mapo-doufu",
        __DIR__"obj/qingcai-fentiao",
        __DIR__"obj/culiu-baicai",
        __DIR__"obj/hongshao-qiezi",
});

void create()
{
        set("short","齋堂");
        set("long",@LONG
這裡便是恆山白雲庵的齋堂。齋堂裡擺滿了長長的餐桌和長凳，幾
位小師太正來回忙碌著布置素齋。南邊通向白雲庵西廊。
LONG);
        set("exits",([ /* sizeof() == 1 */
                "south" : __DIR__"byawest",
        ]));

        set("objects",([
                __DIR__"obj/qingshui-hulu" : 1,
                names[random(sizeof(names))]: 1,
                names[random(sizeof(names))]: 1,
                names[random(sizeof(names))]: 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 30);
        set("coor/y", 3220);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}