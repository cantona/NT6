// changan: prison.c
// by Doing

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "大牢" NOR);
        set("long", @LONG
這裡黑乎乎的，地上的茅草也是濕漉漉的，讓你感到極不舒服，
想起在監外自由自在的日子，你心裡真是萬分難過。
旁邊有一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("no_drift", 1);
        set("item_desc", ([
                "paizi" : "越獄者罪加一等。\n"
        ]));
}

void catch_back(object me)
{
        message_vision(HIM "忽然幾個捕快趕了過來，團團圍住$N"
                       HIM "就是一頓痛毆，邊打邊罵道：“好家"
                       "伙！我讓你跑...”\n\n" NOR, me);

        message("vision", HIY "這群捕快把" + me->name() +
                HIY "打得昏死過去，然後套上枷鎖押走了。\n\n" NOR,
                environment(me), ({ me }));
}

void catch_ob(object me)
{
        message_vision(HIM "忽然張召重趕了過來，一把抓住$N，用鐵鏈鎖住，惡狠"
                       "狠的叫道：“站住！你犯案了，快跟我走吧！”\n\n" NOR,
                       me);

        message("vision", HIY "張召重三拳兩腳把" + me->name() +
                "打暈拎走了。\n\n" NOR,
                environment(me), ({ me }));
}

int free_ob(object me)
{
        string startroom;
        message_vision("兩個獄卒從門外走了出來，架起$N，道：好了，你可以"
                       "走了，要是再敢犯案，哼哼...\n\n", me);
        message("vision", "兩個獄卒和" + me->name() +
                "走了出去... 你不禁嘆了一口氣。\n",
                environment(me), ({ me }));

        tell_object(me, HIR "你被兩個獄卒架著走了出大牢...\n\n" NOR);

        if (me->is_ghost())
                startroom = "/d/death/gate";
        else
                startroom = "/d/changan/baihu1";

        set("startroom", startroom, me);
        me->move(startroom);
        message("vision", "兩個獄卒架著一臉憔悴的" + me->name() +
                          "走了出來，打開枷鎖，哼了一聲就回去了。\n",
                          environment(me), ({ me }));
        return 1;
}
