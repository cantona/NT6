//Cracked by Kafei
// xiangcha.c 香茶
// By Marz 03/29/96

inherit ITEM;

void init();
void do_eat();

void create()
{
        set_name("香茶",({"tea", "cha", "xiang cha"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一杯熱茶，悠悠地冒著香氣～～～\n");
                set("unit", "杯");
                set("value", 300);
        set("remaining", 2);
        set("drink_supply", 50);
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
        
        recover = 5;
        
    if( !this_object()->id(arg) ) return 0;
    if( this_player()->is_busy() )
        return notify_fail("你上一個動作還沒有完成。\n");
    if( query("water", this_player() )
       >= (int)this_player()->max_water_capacity() )
     return notify_fail("你已經喝太多了，再也灌不下一滴水了。\n");

        set("value", 0);
    addn("water", query("drink_supply"), this_player());
    jing=query("jing", this_player());
    e_jing=query("eff_jing", this_player());
    m_jing=query("max_jing", this_player());

// No heal effect for 香茶
/***

    if ( e_jing < m_jing )
        {         
                if ( (e_jing + heal) >= m_jing )
                {
                        set("eff_jing", m_jing, this_player());
                } else
                {        
                        set("eff_jing", e_jing+heal, this_player());
                }        
        } 
***/

        if (jing < e_jing )
        {
        if ( (jing + recover) >= e_jing )
        {
            set("jing", e_jing, this_player());
        } else
        {   
            set("jing", jing+recover, this_player());
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
                    message_vision("$N端起雕花小杯，把剩下的香茶一飲而盡。\n"+
                      "一股香氣直入心脾，$N覺得精神好多了。\n", this_player());
                
                destruct(this_object());
        }

        return 1;
}