// nuerxiang.c 女兒香
// By Marz 04/02/96

inherit ITEM;

void init();
void do_eat();

void create()
{
        set_name("女兒香",({"nuer xiang", "xiang", "tea"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "葉若柳眉，香如處子。這便是茶中極品「女兒香」！\n");
                set("unit", "杯");
                set("value", 8000);
                set("remaining", 1);
                set("drink_supply", 25);
        }
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}


int do_drink(string arg)
{
        int heal, recover, jing, e_jing, m_jing;
        
        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("你上一個動作還沒有完成。\n");
        if( query("water", this_player() )
           >= (int)this_player()->max_water_capacity() )
         return notify_fail("你已經喝太多了，再也灌不下一滴水了。\n");

        set("value", 0);
        addn("water", query("drink_supply"), this_player());

        m_jing=query("max_jing", this_player());
        heal = (int)this_player()->query_con();
        e_jing=query("eff_jing", this_player());

        if ( e_jing < m_jing )
        {         
                if ( (e_jing + heal) >= m_jing )
                {
                        set("eff_jing", m_jing, this_player());
                } else
                {        
                        addn("eff_jing", heal, this_player());
                }        
        } 

        e_jing=query("eff_jing", this_player());
        jing=query("jing", this_player());
        recover = 30+heal;
    
        if (jing < e_jing )
        {
                if ( (jing + recover) >= e_jing )
                {
                        set("jing", e_jing, this_player());
                } else
                {   
                        addn("jing", recover, this_player());
                }   
        }

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        addn("remaining", -1);
        if ( query("remaining") )
        {
                message_vision("$N端起杯香茶，有滋有味地品了幾口。\n"+
                "一股香氣直入心脾，$N覺得精神好多了。\n", this_player());
        } else 
        { 
                 message_vision("$N端起雕花小杯，把裏面的「女兒香」一飲而盡。\n"+
                "一股幽香直入心脾，$N頓時覺得精神大振。\n", this_player());
                destruct(this_object());
        }
        return 1;
}