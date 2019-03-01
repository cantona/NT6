// cigarette.c  by Jane  4.12.1997

inherit ITEM;

int smoking(int);

void create()
{
        string *order = ({"中華","大前門", "柔和七星", "紅塔山", "萬寶路", "希爾頓", "雲煙"});
        set_name( (order[random(7)]), ({ "cigarette" }) );
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一盒香煙，可以(xiyan)。\n");
                set("unit", "盒");
                set("count",6);
                set("value", 50);
        }
}

void init()
{
        add_action("do_smoke", "xiyan");
}

int do_smoke()
{
        object me = this_player();
        object obj = this_object();

        if( query("no_smoke", environment(me)) )
                return notify_fail("這裡不準抽煙！\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢，沒空抽煙！。\n");

        if(query("count") == 6) 
                message_vision("$N抽出一支$n，點著了火，美滋滋地吸了起來。\n", me, this_object());
        else if (query("count") == 1 ) {
                message_vision("$N猛吸了一口剩下的煙屁股，兩個手不由自主地又去模口袋。\n", me);
                destruct(this_object());
                return 1;
        } else 
        switch(random(4)) {
                
                case 0: message_vision("$N吐出一串煙圈，看著它悠閒的散開。\n", me);
                        break;
                case 1: message_vision("$N狠狠的吸了一口$n，大概是吸得太猛了，一張臉漲的通紅。\n", me, obj);
                        break;
                case 2: message_vision("$N吸了一口$n，搖頭晃腦地說道：“飯後一支煙，賽過活神仙。”\n", me, obj );
                        break;
                case 3: message_vision("$N翹起二郎腿，眯上眼睛，猛吸了一口$n，自言自語道：“這東西害人又害己，為啥我還那麼喜歡？”\n", me, obj);
                        break;
                default:
                        break;
        }
        addn("count",-1);
        return 1;
}
