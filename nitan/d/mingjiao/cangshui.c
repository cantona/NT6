// Code of JHSH
// Room: /d/mingjiao/cangshui.c
// Zhangchi 3/00

inherit ROOM;

void create()
{
        set("short", "藏水室");
        set("long", @LONG
此處乃明教洪水旗儲藏毒水之地。室內寒氣逼人。裡面橫擺著數
百個裝滿毒水的大鐵桶。此毒水非比一般，乃用天下致寒的碧水寒潭
潭水配制而成，奇毒無比。無論人畜，一但粘上，片刻之間，皮膚潰
爛，化成血水。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"hsqchanglang",
        ]));
        set("objects",([
                __DIR__"obj/gang" : 1,
        ]));

        set("no_clean_up", 1);
        set("cost", 1);

        setup();
}

void reset()
{
        ::reset();
        set("no_clean_up", 1);
}