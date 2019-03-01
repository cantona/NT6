#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "幹將聖符" NOR, ({ "ganjiang charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "幹將聖符可以將普通道具升級為可SUMMON道具，以後可以隨時\n"
                            "召喚(SUMMON)升級後的道具。\n"
                            "指令格式： upd <欲升級道具ID> to <SUMMON的代號> \n" NOR);
                        
                set("unit", "塊");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_integrate", "upd");
}

int do_integrate(string arg)
{
        object me;
        object ob;
        string filename, content;
        string item, str;
        mapping data;

        if (! arg)
                return notify_fail("你要往什麼道具上使用該聖符？\n");
        
        if (sscanf(arg, "%s to %s", item, str) != 2)
                return notify_fail("指令格式： upd <欲升級道具ID> to <SUMMON的ID> \n");
                
        me = this_player();
        if (! objectp(ob = present(item, me)) &&
            ! objectp(ob = present(item, environment(me))))
                return notify_fail("你身上和附近沒有這樣道具啊。\n");

        if (member_array(F_EQUIP, deep_inherit_list(ob)) == -1 &&
            !query("can_summon", ob) )
                return notify_fail("這類物品無法升級。\n");        
        
        if( query("unique", ob) || ob->is_item_make() || 
            ob->is_character() || ! clonep(ob) || ob->is_no_clone() ||
            query("task_ob", ob) || query("no_store", ob) || 
            query("maze_item", ob) )
                return notify_fail("這個物品無法升級。\n");
        
        if( query("money_id", ob) )
                return notify_fail("你沒用過錢啊？\n"); 
                
        if( query("only_do_effect", ob) || 
            query("food_supply", ob) )
                return notify_fail("這個物品無法升級。\n");
                
        if (sscanf(base_name(ob), "/data/%*s"))      
                return notify_fail("這類物品無法再升級。\n");

        if( query("equipped", ob) )
                return notify_fail("你先卸除他先。\n");

        if( mapp(query("can_summon", me)) && sizeof(query("can_summon", me)) )
        {
                if( member_array(str,keys(query("can_summon", me))) != -1 )
                        return notify_fail("你已經有同樣的SUMMON ID了,請重新換個!\n");
                        
                if( member_array(base_name(ob),values(query("can_summon", me))) != -1 )
                        return notify_fail("這個物品已經升級過了。\n");
        }
                
        message_sort(HIR "\n$N" HIR "用利刃將雙手手心劃破，雙掌貼在" + ob->name() + HIR "上，"
                     "漸漸地，" + ob->name() + HIR "將$N" HIR "的鮮血吸收……\n\n" NOR, me);

        tell_object(me, "你把" + name() + "蓋在" + ob->name() + "上，然後口中念念有詞，\n"
                        "只見聖符化作一道紅光飛入" + ob->name() + "體內！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"發生了不可言喻的變化。\n" NOR);
        
        data = copy(ob->query_entire_dbase());
        data["item_owner"] = query("id", me);
        data["no_sell"] = 1;
        data["no_store"] = 1;
        
        if( filename=TEMPLATE_D->create_file(base_name(ob),query("id", ob),data) )
        {       
                content = @TEXT

int is_no_clone() { return 1; }

TEXT;
                write_file(filename, content);
                
                destruct(ob);    
                catch(call_other(filename, "???"));
                ob = find_object(filename);      
                if (! ob)
                {
                        write("文件出錯，請與巫師聯系！\n");
                        log_file("static/template", sprintf("%s %s creating  %s(%s) had errors.\n",
                                 log_time(),log_id(me),filter_color(ob->name(1)),query("id", ob)));
                        return 1;
                } else
                {
                        ob->move(me, 1);
                        //str = replace_string(str, " ", "-");
                        tell_object(me, HIG "開光成功！以後請用 summon " + 
                                    str + " 來召喚該物品。\n" NOR);
                        log_file("static/template", sprintf("%s %s created  %s(%s)\n",
                                 log_time(), log_id(me),
                                 filter_color(ob->name(1)),query("id", ob)));
                }
                set("can_summon/"+str, base_name(ob), me);
                me->save();
        }                                     

        destruct(this_object());
        return 1;
}

