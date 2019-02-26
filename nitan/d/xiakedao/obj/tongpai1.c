// /d/xiakedao/obj/tongpai1.c
//edit by noz
// Modified by Zeratul Jan 11 2001 銅牌退出不丟，不能給人
/*
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( "賞善銅牌",({"shan pai"}));
          set_weight(100);

          if( clonep() )
                set_default_object(__FILE__);

          set("unit", "塊");
          set("long", "這是一塊閃閃發光的白銅片子，約有巴掌大小，牌子正面刻着一張笑臉，和藹慈祥。\n");
        set("no_put",1);
        set("no_get",1);
        set("no_drop",1);
        set("no_beg",1);
        set("no_steal",1);

        setup();
}

string query_autoload()
{
        if( query("own") != query("id", this_player()) )
                return 0;
        if( time()>query("xkd/time", this_player()) )
                return 0;
        return query("own");
}

void autoload(string param)
{
        string owner;

        if ( !objectp( this_object() ) )
                return;
        if( time()>query("xkd/time", this_player()) )
        {
                destruct( this_object() );
                return;
        }
        if( sscanf(param, "%s", owner)==1 )
                set( "own", owner );
}

int init()
{
        stringlong_msg=query("long", this_object());

          if( query("xkd/time", this_player()) )
                  long_msg+=HIC"牌子背面刻得有字：俠客島於"+CHINESE_D->chinese_date(((query("xkd/time", this_player())-950000000)*60))+"前恭候大駕。\n"NOR;
          set("long", long_msg, this_object());
        return 1;
}
*/

//tongpai1.c
//edit by noz

inherit ITEM;

void create()
{
        set_name( "賞善銅牌", ({"shan pai"}));
        set_weight(100);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是一塊閃閃發光的白銅片子，約有巴掌大小，牌子正"
                            "面刻着一張笑臉，和藹慈祥。\n");
                set("value", 100);
        }

        setup();
}