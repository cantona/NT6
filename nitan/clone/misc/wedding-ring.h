// wedding-ring.h

#include <ansi.h>
#include <armor.h>
#include <command.h>

inherit HANDS;
inherit F_NOCLONE;
inherit F_OBSAVE;

int is_item_make() { return 1; } 
string do_wear();
void set_attrib();

void create()
{
        set_name(HIG "結婚戒指" NOR, ({ "wedding ring", "ring" }) );
        set_weight(100);
        set("material", "gold");
        set("unit", "只");
        set("value", 50000);
        set("no_sell", "這你也要賣？不如把你自己賣了！");
        set("armor_prop/armor", 20);
        set("armor_prop/unarmed", 5);
        set("armor_prop/hand", 5);
        set("armor_prop/strike", 5);
        set("armor_prop/claw", 5);
        set("armor_prop/cuff", 5);
        set("armor_prop/unarmed_damage", 8);
        set("wear_msg", (: do_wear :));
        set("remove_msg", HIG "$N" HIG "把$n" HIG "脫了下來。\n" );
        if (! check_clone()) return 0;

        set("stable", 0);

        setup();
        ::restore();
        set_attrib();
}

void set_attrib()
{
        int per;
        int lvl;
        int tname;
        string desc;

        // 計算對容貌的影響
        lvl = query("enchase/lvl");
        per = query("enchase/point") * lvl / 10000;
        set("armor_prop/per", per);

        // 生成描述
        tname = query("enchase/name");
        desc = query("long");
        if (stringp(tname))
        {
                if (lvl >= 300)
                {
                        desc += HIG "上面鑲嵌著" + tname + HIG
                                "，巧奪天工，美得異乎尋常，讓" + name() +
                                HIG "越發顯得精致。\n" NOR;
                } else
                if (lvl >= 200)
                {
                        desc += HIG "上面鑲嵌著" + tname + HIG
                                "，幾乎沒有瑕疵，可謂人間罕見的珍品。\n" NOR;
                } else
                {
                        desc += HIG "上面鑲嵌著" + tname + HIG
                                "，襯托出" + name() + HIG +
                                "的不俗，只是有些少瑕疵顯得美中不足。\n" NOR;
                }
                set("long", desc);
        }
}

string do_wear()
{
        object me;
        string msg;
        string tname;
        int point;

        me = this_player();
        tname = query("enchase/name");
        point = query("enchase/point");

        if( query("gender", me) == "女性" )
        {
                msg = HIG "$N" HIG "輕巧巧的戴上了一個$n"
                      HIG "，璨然一笑，映的寶光四射，直令得花兒也憔悴了。\n" NOR;
                if (stringp(tname))
                {
                        if (point >= 150)
                                msg += HIG "只見" + tname + HIG "閃過"
                                       "一道光芒，映射得$N" HIG "有若"
                                       "仙子落凡，令人心弛神搖。\n" NOR;
                        else
                        if (point >= 100)
                                msg += HIG "只見" + tname + HIG "閃閃"
                                       "發光，襯托得$N" HIG "說不出的"
                                       "嬌媚。\n" NOR;
                        else
                                msg += HIG "只見" + tname + HIG "閃了"
                                       "一下，照亮了$N" HIG "雋秀的容顏"
                                       "。\n" NOR;
                }
        } else
        {
                msg = HIG "$N" HIG "戴上了一個$n"
                      HIG "，當下意氣風發，神完氣足。\n" NOR;
                if (stringp(tname))
                {
                        if (point >= 150)
                                msg += HIG "只見" + tname + HIG "閃過"
                                       "一道光芒，映射得$N" HIG "如同"
                                       "天神降世，令人目瞪口呆。\n" NOR;
                        else
                        if (point >= 100)
                                msg += HIG "只見" + tname + HIG "閃閃"
                                       "發光，讓$N" HIG "越發顯得挺拔"
                                       "神氣。\n" NOR;
                        else
                                msg += HIG "只見" + tname + HIG "閃了"
                                       "一下，照亮了$N" HIG "的臉龐。\n" NOR;
                }
        }
        return msg;
}

int receive_summon(object me)
{
        object env;
        object temp;

        if ((env = environment()) && env == me)
        {
                write(name() + "不就在你身上嘛？你召喚個什麼勁？\n");
                return 1;
        }

        if (env == environment(me))
        {
                message_vision(HIG "只見地上的" + name() +
                               HIG "化作一道光芒，飛躍至$N" HIW
                               "的掌中！\n\n" NOR, me);
        } else
        {
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        message("vision", HIG "突然" + name() + HIG "化作一道"
                                HIG "光芒消失了！\n\n" NOR, env);

                        if (interactive(env = environment()))
                        {
                                tell_object(env, HIM + name() +
                                                 HIM "忽然離你而去了！\n" NOR);
                        }
                }

                message_vision(HIG "一道光芒劃過，只見$N"
                               HIG "掌中多了一個$n" HIG "！\n\n" NOR,
                               me, this_object());
        }

        move(me, 1);
        if (environment() != me)
                return 1;

        temp=query_temp("armor/"+query("armor_type", me));
        if (temp) temp->unequip();
        WEAR_CMD->do_wear(me, this_object());

        return 1;
}

// 鑲嵌
int do_enchase(object me, object tessera)
{
        object item;
        int lvl;

        item = this_object();
        if( stringp(query("enchase/name", item)) )
                return notify_fail("現在" + item->name() + "上面"
                                   "已經鑲嵌了物品了。\n");

        if (tessera->query_wight() > 100)
                return notify_fail("這件物品也太重了，你怎麼鑲嵌上去啊？\n");

        if (query("equipped"))
                return notify_fail("你現在正戴著它呢，怎麼鑲嵌呢？先脫下來吧。\n");

        if( !query("can_be_enchased", tessera) )
                return notify_fail("天啊，你還沒有這手藝把" +
                                   tessera->name() + "鑲嵌上去。\n");

        if ((lvl = me->query_skill("certosina", 1)) < 100)
                return notify_fail("你的鑲嵌技術不到，無法完"
                                   "成這麼精細活兒。\n");

        message_vision("只聽“喀啦”一聲，$N已經把" + tessera->name() +
                       "規規舉舉的鑲嵌到了$n上面。\n", me, item);
        if (lvl >= 300)
                message_vision("一時間，你只覺得$N寶氣頓生，尊華"
                               "無比，實在是人間神品，沒有半點瑕疵。\n", item);
        else
        if (lvl >= 200)
                message_vision("只見$N寶氣四射，變得越發妍美，庶"
                               "幾沒有半點缺憾。\n", item);
        else
                message_vision("只見$N頓時平添幾分麗色，雖然有"
                               "些小小缺憾，也是瑕不掩瑜。\n", item);
        set("enchase/name", tessera->name());
        set("enchase/point",query("magic/power", tessera));
        set("enchase/lvl", lvl);
        save();
        destruct(tessera);
        set_attrib();

        return 1;
}

// 進行保存數據的接口函數
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ "enchase" : query("enchase") ]);

        if (! objectp(user = environment()))
                data += ([ "user" : query("user") ]);
        else
        if (playerp(user))
                data+=(["user":user->name(1)+"("+query("id", user)+")"]);

        return data;
}

// 接受存盤數據的接口函數
int receive_dbase_data(mixed data)
{
        if (! mapp(data))
                return 0;

        if (mapp(data["enchase"]))
                set("enchase", data["enchase"]);

        if (stringp(data["user"]))
                set("user", data["user"]);

        return 1;
}

int query_autoload() { return 1; }