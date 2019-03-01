// yufu.c
// Date: YZC 96/01/19

inherit KNOWER;

void create()
{
        set_name("漁夫", ({ "yu fu" }) );
        set("gender", "男性" );
        set("age", 62);
        set("long", @LONG
這是一個飽受風霜的老漁夫，雖然不是江湖人士，但是多年在此卻也
和不少武林人士打過交道，知道不少消息秘聞。
LONG );
        setup();
}
