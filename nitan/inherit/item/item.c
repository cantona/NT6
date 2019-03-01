// Written by Lonely@IsMUD.net (05/21/2009)
// item.c

#include <move.h>
#include <name.h>
#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

nosave string s_name;
nosave string s_id;

string to_chinese(int status)
{
        if( status == 0 ) return HIW "普通" NOR;
        else if( status == 1 ) return HIW "普通" NOR;
        else if( status == 2 ) return HIB "優良" NOR;
        else if( status == 3 ) return HIC "珍稀" NOR;
        else if( status == 4 ) return HIM "史詩" NOR;
        else if( status == 5 ) return HIY "傳說" NOR;
        else if( status == 6 ) return HBRED+HIW "神器" NOR;
        else return HBRED+HIY "仙器" NOR;
}

void setup()
{
        seteuid(getuid());
}

void set_name(string name, string *id)
{
        ::set_name(name, id);
        s_name = query("name");
        s_id = query("id");
}

string short()
{
        string colorname;
        string modname, str;
        string status = "";

        if( query("quality_level") )
                status += " "+to_chinese(query("quality_level"));
    
/*
        if( stringp(modname = query("mod_name")) )
                status += " " + modname;
*/
                    
        if( !undefinedp(query("consistence")) && query("consistence") < 1 ) 
        //if( query("endurance") < 1 ) 
                status += HIW" 損"NOR WHT"壞"NOR;
                
        if( !stringp(colorname = query("colorname")) )
                str = s_name + "(" + s_id + ")";
        else
                str = colorname + "(" + s_id + ")";

        if( status != "" )
                str += status;

        return str;
}


int fire(object me, object ob)
{
        string msg;

        if( this_object()->is_item_make() )
                return notify_fail("你累得滿頭大汗，怎麼點也點不著。\n");

        if( stringp(msg = query("no_light")) )
                return notify_fail(msg);

        switch( query("material") )
        {
        case "wood":
                msg = "$N把$n放在$f下面點燃了，火光閃動，漸"
                      "漸只剩下了一團碳粉碎渣。\n";
                break;
        case "leather":
        case "feather":
        case "silk":
                msg = "$N用$f把$n點著了，結果散發出一陣令人難聞的臭味。\n";
                break;
        case "paper":
        case "cloth":
                msg = "$N點著了$n，火苗閃了幾閃，很快就"
                      "燒了個幹幹凈凈，什麼都沒有剩下來。\n";
                break;
        default:
                return notify_fail("這東西看上去沒法點，還是省省力氣吧。\n");
        }

        msg = replace_string(msg, "$n", name());
        msg = replace_string(msg, "$f", ob->name());
        message_vision(msg, me);
        destruct(this_object());
        return 1;
}

string type()
{
        if( this_object()->is_weapon() )
                return "武器";
        if( this_object()->is_unarmed_weapon() )
                return "空手武器";
        else if( this_object()->is_armor() )
                return "防具";
        else if( this_object()->is_food() )
                return "食物";
        else if( this_object()->is_liquid() )
                return "飲具";
        else if( this_object()->is_container() )
                return "容器";
        else if( this_object()->is_book() )
                return "書物";
        else if( this_object()->is_money() )
                return "貨幣";
        else if( this_object()->is_charm() )
                return "護身符";
        else if( this_object()->is_rune() )
                return "符文";
        else if( this_object()->is_tessera() )
                return "鑲嵌物";
        else if( this_object()->is_task() )
                return "任務物品";
        else    return "雜物";
}

mixed query_autoload()
{
        string param;
        mapping data;

        if( !query("auto_load") )
                return 0;

        if( !query("set_data") )
                return 1;

        data = copy(this_object()->query_entire_dbase());
        if( !undefinedp(data["equipped"]) )
                map_delete(data, "equipped");

        param = save_variable(data);
        param = replace_string(param, "\"", "~");
        return param;
}

void autoload(string param)
{
        object shadow_ob;

#ifdef NO_QUIT_DROP
        if( param == "1" )
                return;
#endif

        param = replace_string(param, "~", "\"");
        this_object()->set_dbase(restore_variable(param));
        this_object()->set_name(query("name"), ({ query("id") }));
        if( query("equipped") ) delete("equipped");
        if( shadow_ob = this_object()->query_default_object() )
                set("shadow_ob", shadow_ob);
        return;
}
