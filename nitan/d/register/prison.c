// regiser: prison.c
// by Doing

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "第十八層地獄" NOR);
        set("long", @LONG
這裡極度陰森，你感到無數的鬼魂到處遊盪，駭得你大氣也不敢
透一口，只想趕快離開這裡。也不知道在這裡會呆多久，想到這裡你
不禁感到深深的懊惱。
    旁邊有一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_get", 1); 
        set("no_give", 1); 
        set("no_drop", 1); 
        set("item_desc", ([
                "paizi" : "第十八層地獄，你想翻身？那就試試！\n"
        ]));
}

void init()
{
        add_action("do_suicide", "suicide");
}

int do_suicide()
{
        write("在這冥府你也想自殺，省省吧！\n");
        return 1;
}

void catch_back(object me)
{
        message_vision(HIM "忽然一陣詭秘的煙霧彌漫在四周，兩個青面獠牙"
               "的小鬼跳了出來，一把抓住$N" HIM "，用\n鐵鏈鎖住，惡狠"
               "狠的叫道：“好家伙！我讓你跑...”\n\n" NOR,
               me);

        message("vision", HIY "忽的一道金光，你登時什麼也看不到了...\n\n"
                  HIM "煙霧漸漸的散去... " + me->name() +
                  "不見了？！！\n\n" NOR,
                  environment(me), ({ me }));
}

void catch_ob(object me)
{
        message_vision(HIM "忽然一陣詭秘的煙霧彌漫在四周，兩個青面獠牙"
                       "的小鬼跳了出來，一把抓住$N" HIM "，用\n鐵鏈鎖住，惡狠"
                       "狠的叫道：“站住！你犯案了，快跟我們走吧！”\n\n" NOR,
                       me);

        message("vision", HIY "忽的一道金光，你登時什麼也看不到了...\n\n"
                          HIM "煙霧漸漸的散去... " + me->name() +
                          "不見了？！！\n\n" NOR,
                          environment(me), ({ me }));
}

int free_ob(object me)
{
        string startroom;

        message_vision("忽然兩個小鬼冒了出來，拎住$N，道：好了，你可以"
                       "走了，要是再敢犯案，哼哼...\n\n", me);
        message("vision", "兩個小鬼和" + me->name() + "突然在你面前消"
                          "失了... 你不禁嘆了一口氣。\n",
                          environment(me), ({ me }));

        tell_object(me, HIR "你眼前一黑...\n\n" NOR);

        if (me->is_ghost())
                startroom = "/d/death/gate";
        else
                startroom = "/d/city/wumiao";

        set("startroom", startroom, me);
        me->move(startroom);
        message("vision", "一陣詭秘的煙霧過後，只見" + me->name() +
                          "直挺挺的躺在地上。\n", environment(me), ({ me }));
        return 1;
}
