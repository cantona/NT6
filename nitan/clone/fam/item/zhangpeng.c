

#include <ansi.h>

inherit ITEM;

int is_zhangpeng() { return 1;}

void create()
{
        set_name(HIC "單人帳篷" NOR, ({ "danren zhangpeng", "danren", "zhangpeng"}) );
        set_weight(2000);
                set_max_encumbrance(1000000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("value", 1000000);
                set("long", HIC "這是一個單人帳篷，你可以打開帳篷來休息（指令：openzp)。\n" NOR);
                set("unit", "個");
                                set("no_hand", 1);
                                set("no_steal", 1);
                                set("no_clean_up", 1);
        }
        setup();
}

void init()
{
                add_action("do_open", "openzp");
                add_action("do_close", "closezp");
                add_action("do_out", "outzp");
                add_action("do_enter", "enterzp");
}

// 進入帳篷
int do_enter()
{
                object me, ob;

                me = this_player();
                ob = this_object();
                
                if (ob->query("opening") != me->query("id"))
                        return notify_fail("你目前無法進入這個帳篷。\n");

                if (environment(me) == ob)
                        return notify_fail("你不是已經進來了嗎？\n");

                me->move(ob);
                
                message_vision(HIC "$N一頭鑽進" + ob->name() + HIC "。\n" NOR, me);

                return 1;
}

// 出帳篷
int do_out()
{
                object me, ob;

                me = this_player();
                ob = this_object();

                if (environment(me) != ob)
                        return notify_fail("你並沒有在帳篷裏啊。\n");

                if (! ob->query("out"))
                        return notify_fail("目前無法出帳篷。\n");

                message_vision(HIC "$N鑽出帳篷。\n" NOR, me);

                me->move(ob->query("out"));

                return 1;                        
}

// 打開帳篷
int do_open()
{
                object me;
                object env;
                object obt, obj;
                object *obs;

                me = this_player();

                if (environment(this_object()) != me)return 0;
                                
                if (me->query("danren_zhangpeng/flag"))
                {
                        return notify_fail("你已經有單人帳篷被打開了，不能再打開帳篷。\n");
                }
                
                if (this_object()->query("opening"))
                                return notify_fail("帳篷不是打開的麼？\n");

                env = environment(me);

                if (env->is_zhangpeng())
                                return notify_fail("這個地方不能再打開單人帳篷了。\n");        

                if (! env->query("outdoors"))
                                return notify_fail("帳篷只能在户外打開。\n");
                
                if (me->is_busy() || me->is_fighting())
                                return notify_fail("你現在正忙於做其他事情，無法打開帳篷。\n");
                
                // 一個地點只能開一個帳篷
                obs = all_inventory(env);
                
                foreach(obj in obs)
                {
                        if (obj->is_zhangpeng())
                        {
                                return notify_fail("這個地方已經有人擺帳篷了，你還是換個地方吧。\n");
                        }
                }
                
                obt = new("/clone/fam/item/zhangpeng");

                // 設置主人
                obt->set("opening", me->query("id"));                
                obt->set("no_get", 1);
                
                // 設置描述
                obt->set("long", HIW "這是一個單人帳篷，你可以收起帳篷(指令：closezp）。\n"
                                 HIW "****如果覺得悶了可以到外面透透氣(outzp），進入帳篷使用指令（enterzp）。\n" NOR);

                // 設置特殊屬性
                obt->set("sleep_room", 1);
                obt->set("no_fight", 1);

                // 設置出口
                obt->set("out", file_name(env));

                message_vision(HIC "$N打開" + this_object()->name() + HIC "一頭鑽了進去。\n" NOR, me);

                me->move(obt);
                obt->move(env);

                // 設置特殊標誌
                me->set("danren_zhangpeng/flag", 1);
                me->set("danren_zhangpeng/ob", obt);
                
                me->save();

                destruct(this_object());

                return 1;
}

int do_close(string arg)
{
                object me, obt;
                object *obs;
                object obj, newob;

                me = this_player();
                obt = this_object();

                if (! obt->query("opening"))
                                return notify_fail("單人帳篷不是關閉着的麼？\n");

                if (obt->query("opening") != me->query("id"))
                                return notify_fail("你沒有權利收起這個帳篷。\n");

                // 複製一個帳篷給該玩家
                newob = new("/clone/fam/item/zhangpeng");
                
                message_vision(HIW "$N將帳篷收了起來，裝進行囊。\n" NOR, me);

                // 檢查負重
             if (newob->query_weight() + me->query_encumbrance() >= me->query_max_encumbrance())
                {
                                tell_object(HIR "對不起，你的負重不足，無法收起這個帳篷。\n" NOR);
                                destruct(newob);
                                return 1;
                }

                // 想將帳篷裏的人移出來，然後摧毀帳篷，最後複製一個帳篷給該玩家
                obs = all_inventory(obt);

            // 將帳篷裏的人都移出來
                if (sizeof(obs))
                {
                        foreach(obj in obs)
                        {
                                obj->move(environment(obt));
                        }
                }

        // 將複製的帳篷給該玩家
                newob->move(me, 1);

                me->delete("danren_zhangpeng");

                me->save();
                // 摧毀這個帳篷
                destruct(this_object());

                return 1;
                
}

int query_autoload()
{
                return 1;
}