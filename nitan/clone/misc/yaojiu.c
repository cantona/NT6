// yaojiu.c
#include <ansi.h>

inherit ITEM;
int do_pour(string arg);

void create()
{
        set_name("藥臼", ({ "yao jiu", "jiu" }) );
        set("long",
                "這是一個藥臼，是醫士們用來煉製丹藥的容器：\n"
                "put <藥材>          將藥材放入藥臼中。\n"
                "fill                向藥臼中添加清水。\n"
                "burn                點火折燃燒木柴。\n"
                "putout              滅火冷卻藥臼。\n"
//                "get <丹藥>          取出丹藥。\n"
        );
        set_weight(3000);
        set_max_encumbrance(5000);
        set("unit", "個");
        set("no_drop", 1);
        set("no_steal", 1);
        set("no_put", 1);
        set("no_beg", 1);
        set("no_get", 1);
        set("no_insert", 1);
        set("process", 0);

        seteuid(getuid());
}

int is_container() { return 1; }

void init()
{
        object ob;
        add_action("do_fill", "fill");
        add_action("do_burn", "burn");
        add_action("do_putout", "putout");
}

int do_fill(string arg)
{
        object room = environment(this_player());

        if (!present(this_object(), this_player()))
                return 0;

        if (!arg || arg != "water")
                return notify_fail("你要往藥臼裏添加什麼？\n");
        if (query("process") > 0)
                return notify_fail("你已經往藥臼裏添過水了啦！\n");
        if( !query("resource/water", room) )
                return notify_fail("這裏沒有水。你找個有水之處再添水吧。\n");
        set("process", 1);
        message_vision("$N往藥臼裏添了些清水。\n", this_player());
        return 1;
}
int do_burn()
{
        object *inv = all_inventory(this_object());
        object room = environment(this_player());
        object me = this_player();
        int seq, i = 0, j = 0;

        if (!present(this_object(), this_player()))
                return 0;

        if (!wizardp(me))
        {
                if (query("process") == 0)
                        return notify_fail("還沒放水就點火，想幹燒啊！\n");
                if (query("process") != 1)
                        return notify_fail(HIY"現在不用你再點火了啦！\n"NOR);
                if (!present("fire", me))
                        return notify_fail("你身上沒有帶火折。這回糟了吧。\n");
                if(!present("mu chai",me) && !present("mu chai",room))
                        return notify_fail("點燃火折你才發現沒有木柴可燒。\n");
        }
        set("process", 2);
        set("burntime", time());
        message_vision("$N掏出火折一晃，火折亮了起來。火折點燃木柴後，再把藥臼放在柴上。\n", this_player());
        for ( seq = 0; seq < sizeof(inv); seq++)
        {
                if( !query("vegetable", inv[seq]) )
                {
                        set("process", 3);
                        message_vision("藥臼裏混進不能入藥的東西。看來這臼藥沒用了。。。\n", this_player());
                }
                i+=query("vegetable", inv[seq]);
                j+=query("nostrum", inv[seq]);
                destruct(inv[seq]);
        }
        message_vision("過了一會藥臼裏冒出一股淡淡的白氣。藥材漸漸熬到水中。。。\n", this_player());
        set("vegetable", i);
        set("nostrum", j);
        return 1;
}
int do_putout()
{
        string *dir, target = "shit";
        object obj, room = environment(this_player());
        int i;

        if (!present(this_object(), this_player()))
                return 0;

        seteuid(getuid());
        if (query("vegetable") == 0)
                return notify_fail("藥臼裏沒有藥材，熬不成藥了！\n");
        if (query("process") < 2)
                return notify_fail("現在沒有火可滅了啦！\n");
        if (time() - query("burntime") < 180 && !wizardp(this_player()))
                return notify_fail("藥正在熬，火候還沒到，現在可滅不得火！\n");
        if (time() - query("burntime") > 300 && !wizardp(this_player()))
        {
                set("process", 0);
                return notify_fail("藥好像熬了太久，火候過了，藥熬糊了！\n");
        }
        message_vision("$N撤了着火的木柴，讓藥臼自行冷卻。\n", this_player());
        if (query("process") == 3)
        {
                set("process", 0);
                return notify_fail("肯定是藥臼中摻進雜質了，這次藥沒熬成！\n");
        }
        set("process", 0);
        dir = get_dir("/clone/medicine/nostrum/");
        for (i=0; i<sizeof(dir); i++)
        {
                obj = new( "/clone/medicine/nostrum/" + dir[i] );
                if( query("vegetable", obj) == query("vegetable") && 
                        query("nostrum", obj) == query("nostrum") )
                {
                        target = dir[i];
                }
                destruct(obj);
        }
        if(obj = new("/clone/medicine/nostrum/"+target))
        {
                if( query("level", obj)<this_player()->query_skill("medicine",1) )
                {
                        obj->move(this_player());
                        obj->move(this_object());
                        message_vision("$N終於煉出一"+query("unit", obj)+query("name", obj)+"。\n",this_player());
                        addn("medicine_count", 1, this_player());
                }
                else
                {
                        destruct(obj);
                        obj = new("/clone/medicine/nostrum/shit");
                        obj->move(this_object());
                        message_vision("可能是$N醫術不精，煉出一"+query("unit", obj)+query("name", obj)+"。\n",this_player());
                }
                return 1;
        }
        else return notify_fail("可能是因為配方不太對，這次熬藥沒成功！\n");
}
