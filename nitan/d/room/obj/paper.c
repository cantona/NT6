// paper.c
//
// 紙張可以用來作畫，畫好以後可以作為autoload物品載入。
// 保存的必要信息：
// draw/type    圖畫的類型
// draw/content 圖畫的描述
// draw/info    圖畫的附加信息

#include <ansi.h>
#include <command.h>

inherit ITEM;

void create()
{
        set_name("紙張", ({"paper", "paper of drawing"}));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張普普通通的白紙，上面什麼也沒有。"
                            "如果你願意可以畫(draw)點東西在上面。\n");
                set("material", "paper");
                set("can_draw", 1);
        }
}

void init()
{
        add_action("do_draw", "draw");
        add_action("do_clear", "clear");
}

int do_draw(string arg)
{
        object me;
        object ob;
        int lvl;

        if (! arg)
                return notify_fail("你想畫什麼？如果要畫這裏的風景，"
                                   "可以draw here。\n");

        me = this_player();
        lvl = me->query_skill("drawing", 1);
        if (arg != "here" && ! objectp(ob = present(arg, environment(me))))
                return notify_fail("這裏沒有你想要畫的東西。\n");

        if (query("draw"))
                return notify_fail("這張紙已經畫了東西，如果想再畫需要"
                                   "先抹去(clear)。\n");

        message("vision", me->name() + "拿出一支筆，在紙上不知"
                "道畫了些什麼。\n", environment(me), ({ me }));

        if (arg == "here")
        {
                tell_object(me, "你拿出一支筆，仔細的臨摹這裏的風景。\n");
                if (lvl < 30)
                {
                        tell_object(me, "可是你的畫畫技巧實在是太差了，"
                                        "無從落筆，只好胡亂塗抹一陣。\n");
                        set("draw/content", "上面亂七八糟的看不出畫的是"
                                            "什麼。\n");
                        set("draw/info", "unknow");
                } else
                if (lvl < 80)
                {
                        tell_object(me, "雖然你的畫畫技巧不怎麼樣，但是"
                                        "好在學過一點，勉強畫得。\n");
                        set("draw/content", "上面畫的雖然有些凌亂，但是"
                            "還能看得出是" + environment(me)->short() +
                            "的風景。\n");
                        set("draw/info", base_name(environment(me)));
                } else
                {
                        tell_object(me, "你隨意揮灑，風景登時飄然躍在紙"
                                        "上。\n");
                        set("draw/content", "上面畫的是" + environment(me)->short() +
                            "的風景，極為傳神，宛若親臨。\n");
                        set("draw/info", base_name(environment(me)));
                }                

                set("draw/type", "風景");
        } else
        if (ob->is_character())
        {
                if (ob != me)
                {
                        message("vision", me->name() + "不住的打量" + ob->name() +
                                "，手下不知道在畫些什麼東西。\n",
                                me, ob);
                        tell_object(me, "你拿出一支筆，仔細的臨摹" + ob->name() + "。\n");
                } else
                {
                        command("consider");
                        tell_object(me, "你拿出一支筆，仔細的按照記憶中的樣子描繪自己。\n");
                }
                if (lvl < 30)
                {
                        tell_object(me, "可是你的畫畫技巧實在是太差了，"
                                        "無從落筆，只好胡亂塗抹一陣。\n");
                        set("draw/content", "上面亂七八糟的看不出畫的是"
                                            "什麼。\n");
                        set("draw/info", "unknow");
                } else
                if (lvl < 80)
                {
                        tell_object(me, "雖然你的畫畫技巧不怎麼樣，但是"
                                        "好在學過一點，勉強畫得。\n");
                        set("draw/content", "上面畫的雖然有些凌亂，但是"
                            "還能看得出是" + ob->name() + "，有點神似。\n");
                        set("draw/info",query("id", ob));
                } else
                {
                        string msg;
                        object cloth;

                        tell_object(me, "你隨意揮灑，" + ob->name() +
                                        "登時飄然躍在紙上。\n");
                        msg = "攤看紙來，";
                        if (userp(ob))
                        {
                                cloth=query_temp("armor/cloth", ob);
                                if( query("gender", ob) == "女性" )
                                {
                                        if (cloth)
                                                msg += "只見上面一名女子身着" + cloth->name() + "，";
                                        else
                                                msg += "只見上面一名女子一絲不掛、未着寸縷，";
                                } else
                                {
                                        if (cloth)
                                                msg += "只見上面一名男子身着" + cloth->name() + "，";
                                        else
                                                msg += "只見上面一名男子坦胸露乳，赤身裸體，";
                                }
                                msg += LOOK_CMD->description(ob);
                        }
                        msg += "原來上面畫的是" + ob->name() +
                            "，果然傳神之至，庶幾破紙而出。\n";
                        set("draw/content", msg);
                        set("draw/info",query("id", ob));
                }                

                set("draw/type", "人物");
        } else
        {
                tell_object(me, "你拿出一支筆，仔細的臨摹" + ob->name() + "。\n");
                if (lvl < 30)
                {
                        tell_object(me, "可是你的畫畫技巧實在是太差了，"
                                        "無從落筆，只好胡亂塗抹一陣。\n");
                        set("draw/content", "上面亂七八糟的看不出畫的是"
                                            "什麼。\n");
                        set("draw/info", "unknow");
                } else
                if (lvl < 80)
                {
                        tell_object(me, "雖然你的畫畫技巧不怎麼樣，但是"
                                        "好在學過一點，勉強畫得。\n");
                        set("draw/content", "上面畫的雖然有些凌亂，但是"
                            "還能看得出是" + ob->name() + "，有點神似。\n");
                        set("draw/info",query("id", ob));
                } else
                {
                        string msg;
                        object cloth;

                        tell_object(me, "你隨意揮灑，" + me->name() +
                                        "登時飄然躍在紙上。\n");
                        msg = "上面畫的是" + ob->name() +
                            "，逼真之極。\n";
                        set("draw/content", msg);
                        set("draw/info",query("id", ob));
                }                

                set("draw/type", "物品");
        }

        set("no_sell", 1);
        set("value", 1);

        return 1;
}

int do_clear(string arg)
{
        object me = this_player();

        if (! arg || ! id(arg))
                return notify_fail("你要擦乾淨什麼東西？\n");

        if (! query("draw/type"))
        {
                write ("上面乾乾淨淨的什麼也沒有，不用再擦了。\n");
                return 1;
        }

        message_vision("$N輕輕的將紙插抹乾淨。\n", me);
        delete("draw");
        delete("no_sell");
        delete("value");
        return 1;
}

string long()
{
        return query("draw/type") ? query("draw/content") : query("long");
}

string query_autoload()
{
        mapping draw;

        if (! mapp(draw = query("draw")))
                return 0;

        return draw["type"] + "|" + draw["content"] + "|" + draw["info"];
}

void autoload(string param)
{
        string type;
        string content;
        string info;

        if (sscanf(param, "%s|%s|%s", type, content, info) != 3)
        {
                destruct(this_object());
                return;
        }

        set("no_sell", 1);
        set("value", 1);
        set("draw/type", type);
        set("draw/content", content);
        set("draw/info", info);
}