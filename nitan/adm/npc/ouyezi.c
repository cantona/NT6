// Written by Lonely@chinamud.cn

#include <ansi.h>
inherit NPC;

int ask_blue();
int ask_pink();
int ask_gold();
int ask_green();
int ask_steady();
int do_combine(object me, object ob);
int do_finish(object me, object ob);
mapping upgrade_material = ([
        "blue" : ([ "/clone/item/bcrystal" : 3, ]),
        "pink" : ([ "/clone/item/pcrystal" : 1,
                    "/d/item/obj/xuantie"  : 3, ]),
        "gold" : ([ "/clone/item/ycrystal" : 2, ]),
        "green" : ([ "/clone/item/gcrystal" : 1,
                     "/d/item/obj/xuantie" : 5, ]),
        "steady" : ([ "/clone/item/bcrystal" : 1,
                      "/d/item/obj/xuantie" : 4,
                      "/clone/item/mcrystal" : 1, ]),
        //"increase":
]);

void create()
{
        set_name("歐冶子", ({ "ouye zi", "zi" }) );
        set("nickname", RED "赤心劍膽" NOR );
        set("gender", "男性" );
        set("age", 60);
        set("long",
                "他頭上包著頭巾，三縷長髯飄洒胸前，面目清瘦但紅暈有光，\n"
                "二目炯炯有神，爍爍閃著竟似是凜凜的劍光，渾身似乎都包圍\n"
                "在一股劍氣之中。\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 30);
        set("shen_type", 0);
        set("max_neli",5000);
        set("jiali",50);
        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("jiuyin-baiguzhao",200);
        set_skill("force",150);
        set_skill("sword",150);
        set_skill("bibo-shengong",100);
        set_skill("luoying-shenjian",100);
        set_skill("parry",90);
        set_skill("anying-fuxiang",100);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",50);
        create_family("玄天派", 1, "弟子");
        set("combat_exp", 250000);

        map_skill("force","bibo-shengong");
        map_skill("parry","luoying-shenjian");
        map_skill("sword","luoying-shenjian");
        map_skill("unarmed","jiuyin-baiguzhao");
        map_skill("dodge","anying-fuxiang");

        set("attitude", "peaceful");

        set("inquiry", ([
                "鑄劍" : "我已經很久很久沒有鑄劍了，你還是另找別人吧。\n",
                "籃裝" : (: ask_blue() :),
                "粉裝" : (: ask_pink() :),
                "金裝" : (: ask_gold() :),
                "綠裝" : (: ask_green() :),
                "強化" : (: ask_steady() :),
        ]) );
        setup();
        set("chat_chance", 3);
        set("chat_msg", ({
                "歐冶子撫劍而歌：巨闕神兵兮，人鑄就。蓋世寶劍兮，配英雄！\n",
                "歐冶子低頭沉吟，似乎在思考什麼。\n"
                "歐冶子嘆了一口氣：神兵配英雄，可英雄。。。。。。\n"
        }) );
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        add_action("do_show", "show");
}

int ask_blue()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N對$n" CYN "說道：你是要合成籃色裝備嗎？你先付給我一萬兩黃金，然後把以下材料準備好給我。\n"
                "       1、想要合成的白色裝備 1 個\n"
                "       2、相同等級已經吸取屬性的黑水晶或超級黑水晶 3 個\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "blue", me);
        return 1;
}

int ask_pink()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N對$n" CYN "說道：你是要合成粉色裝備嗎？你先付給我一萬兩黃金，然後把以下材料準備好給我。\n"
                "       1、想要合成的藍色裝備 1 個\n"
                "       2、粉水晶或超級粉水晶 1 個\n"
                "       3、玄鐵石 3 個\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "pink", me);
        return 1;
}

int ask_gold()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N對$n" CYN "說道：你是要合成金色裝備嗎？你先付給我一萬兩黃金，然後把以下材料準備好給我。\n"
                "       1、想要合成的粉色裝備 1 個\n"
                "       2、黃水晶或超級黃水晶 2 個\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "gold", me);
        return 1;
}

int ask_green()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N對$n" CYN "說道：合成套裝(綠裝)必需的道具如下
       1）1件需求等級為30 級以上（包含30級）的金裝備
       2）1塊綠水晶
       3）5 塊金色名字的煉化材料（玄鐵石)
你如果準備好了道具，先交給我1萬兩黃金。\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "green", me);
        return 1;
}

int ask_steady()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N對$n" CYN "說道：強化必需的道具如下
       1）1件需求等級為30 級以上（包含30級）的藍裝備（粉裝備、金裝備、綠裝備）
       2）1塊聖水晶
       3）1顆吸取了附加屬性的黑水晶（超級黑水晶）
       4）4 塊金色名字的煉化材料（玄鐵石)
你如果準備好了道具，先交給我1萬兩黃金。\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "steady", me);
        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;

        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len ))
        {
                write(sprintf("對不起，中文字必須是 1 到 %d 個中文字。\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 9 && ! is_chinese(name))
        {
                write("對不起，請您用「中文」為套裝取名字。\n");
                return 0;
        }
        return 1;
}


void get_modname(string arg, object me, object ob)
{
        string arg_old;

        if( arg == "q" || arg == "Q" ) {
                write("你取消了綠化裝備，將裝備取回。\n");
                ob->move(me, 1);
                return;
        }
        arg_old = arg;
        arg = trans_color(arg, 3);
        arg = filter_color(arg, 1);

        if (! check_legal_name(arg, 8))
        {
                write("請給你的綠化裝備起個後綴名稱(不要超過4個字，可加顏色)：\n");
                input_to( (: get_modname :), me, ob);
                return;
        }

        arg = arg_old;
        arg = trans_color(arg, 3);
        arg = HIG "※" NOR+arg+NOR+HIG "※" NOR;
        set_temp("upgrade/modname", arg, me);

        do_combine(me, ob);
        return;
}

int accept_object(object me, object ob)
{
        string *obj, str;
        mapping nds, data;
        int i;

        if( query_temp("upgrade/making") ) {
                message_vision("$N對$n說：我現在正忙著呢，請稍等一會！\n",
                               this_object(), me);
                return 0;
        }

        if( query("money_id", ob)){
                if( !query_temp("upgrade/money", me)){
                        message_vision("$N把$n遞過去的" + ob->name() +
                                       "推了回來，道：無功不受祿！\n",
                                       this_object(), me);
                        return 0;
                }

                if( ob->value()<query_temp("upgrade/money", me)){
                        message_vision("$N對$n說：對不起，老夫這一"
                                       "千多年來，還沒有打過折扣。\n",
                                       this_object(), me);
                        return 0;
                }
                if( query_temp("upgrade/do", me) == "steady" )
                        message_vision("$N對$n說道：好，你這就把你的要強化的裝備給我看看(show)先。\n",
                                this_object(), me);
                else
                        message_vision("$N對$n說道：好，你這就把你的要合成的裝備給我看看(show)先。\n",
                                this_object(), me);

                set_temp("paid/歐冶子", 1, me);
                destruct(ob);
                return -1;
        }

        if( !mapp(nds=query_temp("upgrade/needs", me)) && !query_temp("upgrade/prepare", me)){
                message_vision("$N對$n說：你給我這個幹什麼啊！\n",
                               this_object(), me);
                return 0;
        }

        if( query("material_file", ob) && base_name(ob) == query_temp("upgrade/file", me)){
                if( query_temp("upgrade/prepare", me)){
                        if( query_temp("upgrade/do", me) == "green"){
                                write("請給你的綠化裝備起個後綴名稱(不要超過4個字，可加顏色)：\n");
                                input_to( (: get_modname :), me, ob);
                        }
                        else
                                do_combine(me, ob);
                        return 1;
                } else {
                        message_vision("$N對$n說：你給我這個幹什麼啊！\n",
                                              this_object(), me);
                        return 0;
                }
        }

        if( !mapp(nds) ) return 0;

        obj = keys(nds);
        for( i = 0; i < sizeof(obj); i++ ) {
                if( ob->query_name() == obj[i]->query_name() ) {
                        if( ob->query_name() == "黑水" ) {
                                if( query_temp("upgrade/level", me) && 
                                    query("enchase/level", ob) != query_temp("upgrade/level", me)){
                                        message_vision("$N對$n說：" + ob->name() + "的等級和要求不符！\n",
                                                this_object(), me);
                                        return 0;
                                }
                                if( query_temp("upgrade/type", me) && 
                                    query("enchase/type", ob) != query_temp("upgrade/type", me)){
                                        message_vision("$N對$n說：" + ob->name() + "的類型和要求不符！\n",
                                                this_object(), me);
                                        return 0;
                                }
                                str=keys(query("enchase/apply_prop", ob))[0];
                                if( query_temp("upgrade/do", me) == "steady"){
                                        if( !query_temp("upgrade/steady_prop/"+str, me)){
                                                message_vision("$N對$n說：" + ob->name() + "所吸取的屬性和用來強化的裝備原始屬性不一致，不可用來強化！\n",
                                                        this_object(), me);
                                                return 0;
                                        }
                                        set_temp("upgrade/apply_prop/"+str,query("enchase/apply_prop/"+str,  ob), me);
                                } else {
                                        if( query_temp("upgrade/apply_prop/"+str, me)){
                                                message_vision("$N對$n說：" + ob->name() + "所吸取的屬性不可重復用來合成！\n",
                                                        this_object(), me);
                                                return 0;
                                        }
                                        set_temp("upgrade/apply_prop/"+str,query("enchase/apply_prop/"+str,  ob), me);
                                }
                        }
                        nds[obj[i]] = nds[obj[i]] - 1;
                        if( nds[obj[i]] < 1 ) {
                                map_delete(nds, obj[i]);
                        }
                        destruct(ob);
                        set_temp("upgrade/needs", nds, me);

                        if( !mapp(nds=query_temp("upgrade/needs", me)) || sizeof(keys(nds))<1){
                                set_temp("upgrade/prepare", 1, me);
                                delete_temp("upgrade/needs", me);
                                tell_object(me, HIR "\n合成裝備的物品齊了，現在把你的要合成的裝備給我吧！\n" NOR);
                                return -1;
                        }

                        tell_object(me, HIR "\n恩，不錯，還有沒有了？！\n" NOR);
                        return -1;
                } else {
                        message_vision("$N對$n說：你給我這個幹什麼啊？我要你找的材料不是這個！\n",
                                   this_object(), me);
                        return 0;
                }
        }
}

int do_combine(object me, object ob)
{
        mapping data, temp, prop, prop2;
        int rate, level, value;
        string combine_to, type, str;

        set_temp("upgrade/making", ob);
        set_temp("upgrade/player_id",query("id", me));

        message_vision(HIM "$N拿出特制的魔方，將" + ob->name() + HIM "和合成材料放了進去。\n"
                       "接著$N按照特殊的順序將魔方旋轉，霎時間只見魔方發出一道奇異的光芒，\n"
                       "一"+query("unit", ob)+"嶄新的"+ob->name()+HIM"出現在你的眼前。\n\n"NOR,
                       this_object(), me);

        temp = ([]);
        level=query("require/level", ob);
        temp["level"] = level;
        rate = random(100);
        if( rate < 40 ) temp["str"] = level + random(level);
        else if( rate < 60 ) temp["con"] = level + random(level);
        else if( rate < 80 ) temp["dex"] = level + random(level);
        else temp["int"] = level + random(level);

        if( ob->is_weapon() || ob->is_unarmed_weapon() ) type = "weapon";
        else type=query("armor_type", ob);
        prop = EQUIPMENT_D->apply_props(type, level, 2);
        prop2 = EQUIPMENT_D->apply_props("ultimate", level, 1);
        if( type == "weapon" ) {
                map_delete(prop, "damage");
        } else {
                map_delete(prop, "armor");
        }

        combine_to=query("combine_to", ob);
        if( query_temp("upgrade/do", me) == "steady"){
                str=keys(query_temp("upgrade/apply_prop", me))[0];
                value = random(EQUIPMENT_D->query_prop_value(str, level))+1;
                set("enchase/apply_prop/"+str, value, ob);
                addn("enchase/steady", 1, ob);
        }
        else if( combine_to == "blue" ) {
                data=copy(query_temp("upgrade/apply_prop", me));
                set("enchase/apply_prop", data, ob);
                set("enchase/flute", 3, ob);
                set("enchase/used", 3, ob);
                ob->set_color("$HIB$");
                set("combine_to", "pink", ob);
                set("require", temp, ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"出品\n"NOR, ob);
        }
        else if( combine_to == "pink" ) {
                set("enchase/pink_prop", prop, ob);
                addn("enchase/flute", 1, ob);
                addn("enchase/used", 1, ob);
                ob->set_color("$HIM$");
                set("combine_to", "gold", ob);
                set("require", temp, ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"出品\n"NOR, ob);
        }
        else if( combine_to == "gold" ) {
                ob->set_color("$HIY$");
                set("combine_to", "green", ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"出品\n"NOR, ob);
        }
        else if( combine_to == "green" ) {
                set("enchase/green_prop", prop, ob);
                set("enchase/mod_prop", prop2, ob);
                set("modname",query_temp("upgrade/modname",  me), ob);
                set("mod", "itemmake", ob);
                ob->set_color("$HIG$");
                set("combine_to", "ultimate", ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"出品\n"NOR, ob);
        }

        ob->save();

        remove_call_out("do_finish");
        call_out("do_finish", 1, me, ob);
        return 1;
}

int do_finish(object me, object ob)
{
        if( !objectp(me) )
                me = find_player(query_temp("upgrade/player_id"));

        if( !objectp(me) || environment(me) != environment() ) {
                message_vision(HIW "$N嘆了口氣，說道：客人為何這就去"
                               "了！？罷了罷了，不做了，去吧！\n"
                               "$N把"+ob->name()+"拋進火爐，就此不見。\n\n" NOR,
                               this_object());
                if( objectp(me) )
                        delete_temp("upgrade", me);

                if( objectp(ob) && present(ob, this_object()) )
                        destruct(ob);

                delete_temp("upgrade");
                return 1;
        }
        ob->move(me, 1);
        message_vision("$N把"+query("name", ob)+"交還給了$n。\n",
                       this_object(), me);
        delete_temp("upgrade", me);
        delete_temp("upgrade");
        return 1;
}

int do_show(string arg)
{
        object money;
        object ob, item;
        object me;
        string *obs;
        string str, type;
        mapping data;
        int level, i;

        if( query_temp("upgrade/making") )
                return notify_fail("我正在忙著呢，請稍等一會！\n");

        if( !arg )
                return notify_fail("你要亮出什麼東西？\n");

        me = this_player();
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上沒有這種東西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n");

        if( query_temp("upgrade/file", me) )
                return notify_fail("你先把你正在進行的合成/強化/改造完工了再說！\n");

        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "對$N說：“拜托拜托...”\n",
                       this_object(), me);

        if( !wizardp(me) && !query_temp("paid/歐冶子",1, me)){
                command("say 你這是想讓我幫你幹什麼呢？");
                /*command("heihei");
                set_temp("upgrade/money", 100000000, me);
                command("say 這...怎麼也的有點意思意思吧？你"
                        "說一萬兩黃金怎麼樣？當然多些我也不反對。");*/
                return 1;
        }

        if( !query("material_file", ob)){
                command("heng");
                command("say 這...這...我看還是算了吧！");
                return 1;
        }

        /*if( ob->item_owner() != query("id", me)){
                command("kick"+query("id", me));
                command("say 你以為我的仙術是蒙事的啊，這分明不是你的！");
                return 1;
        }*/
        if( query_temp("upgrade/do", me) == "steady"){
                data = copy(upgrade_material["steady"]);
                level=query("require/level", ob);

                if( query("skill_type", ob) )
                        type=query("skill_type", ob);
                else
                        type=query("armor_type", ob);

                set_temp("upgrade/type", type, me);
                set_temp("upgrade/level", level, me);
                set_temp("upgrade/steady_prop", copy(query("enchase/apply_prop", ob)), me);
        } else {
                data=copy(query("combine_to", upgrade_material[ob)]);
                if( !mapp(data) ) return notify_fail("你的裝備已經不需要再合成了。\n");

                if( query("combine_to", ob) == "blue"){
                        level=query("require/level", ob);

                        if( query("skill_type", ob) )
                                type=query("skill_type", ob);
                        else
                                type=query("armor_type", ob);

                        set_temp("upgrade/type", type, me);
                        set_temp("upgrade/level", level, me);
                }
        }
        set_temp("upgrade/file", base_name(ob), me);
        set_temp("upgrade/needs", data, me);
        obs = keys(data);

        if( query_temp("upgrade/do", me) == "steady" )
                str = "\n你的" + ob->short() + HIG + "此次強化需要的物品如下：\n\n";
        else
                str = "\n你的" + ob->short() + HIG + "此次合成需要的物品如下：\n\n";
        for( i=0; i<sizeof(obs); i++ ) {
                item = new(obs[i]);
                str += sprintf("%-40s ：\t%d %s\n",
                               item->short(),
                               data[obs[i]],
                               query("unit", item));
                destruct(item);
        }
        str += "\n";
        tell_object(me, HIG + str + NOR);
        tell_object(me, "你千萬要記好我叫你找的的物品，否則.....\n");
        tell_object(me, "你把" + ob->short() + "所需的物品備齊，再來找我吧！\n");
        delete_temp("paid/歐冶子", me);
        return 1;
}

void kill_ob(object ob)
{
        ::kill_ob(ob);
        message_vision("$N冷笑一聲，道：“這年頭，什麼人都有。”說完伸手一指$n。\n",
                       this_object(), ob);
        ob->unconcious();
}

int accept_fight(object who)
{
        command("say 沒興趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是眼前一花，看不太清楚。\n");
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}