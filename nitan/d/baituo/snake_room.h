// Code of JHSH
// snake_room.h 蛇谷中有蛇的房間

void check_snake(object, string);
void smoke_snake(object, object, string);
#include <ansi.h>

void init()
{
        object here = this_object();
        set("can_perform_shewu", 1, here);
        set("enter_shegu", 1, this_player());
        delete_temp("search", this_player());

        if( query("hide_snake", here)<1 && 
        (time()-query("last_search", here)>180 || !query("last_search", here)) )
                set("hide_snake", 1+random(3), here);

        add_action("do_search", "search");
        add_action("do_use","use");
        add_action("do_burn","burn");
}

string look_bush()
{
        string desc;
        if(!query("searched/bush")) desc = "一處低矮的灌木叢。\n";
        else desc = "一處低矮的灌木叢，地上有些斷折掉落的枝葉。\n";        
        return desc;
}

string look_crack()
{
        string desc;
        if(!query("searched/crack")) desc = "樹根間的裂縫，旁邊生著叢叢亂草。\n";
        else desc = "樹根間的裂縫，附近的雜草倒向兩邊，似乎被撥動過。\n";        
        return desc;
}

string look_cave()
{
        string desc;
        if(!query("searched/cave")) desc = "山壁下的一個小洞，洞口土地沒什麼砂土，頗為光滑。\n";
        else desc = "山壁下的一個小洞，洞口土地有些枝葉燒剩的灰燼。\n";        
        return desc;
}

int do_search(string arg)
{
        object me, here, weapon;
        string place;
        
        me = this_player();
        here = this_object();
        weapon=query_temp("weapon", me);

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙著呢。\n");

        if( !objectp(weapon) || (query("skill_type", weapon) != "staff"
         && query("skill_type", weapon) != "club"
         && query("skill_type", weapon) != "stick") )
                return notify_fail("空手尋蛇太危險了，先拿點趁手的工具吧。\n");


        if(arg == "grass" && query("grass") ) {
                place = "草叢";
                message_vision("$N用"+weapon->name()+"撥動附近的草叢。\n", me);
                addn("jingli", -20, me);
                set("searched/grass", 1);
        }
        
        else if(arg == "bush" && query("bush") ) {
                place = "樹叢";
                message_vision("$N揮著"+weapon->name()+"，打動四周的樹叢枝葉，發出沙沙的輕響。\n", me);
                addn("jingli", -40, me);
                set("searched/bush", 1);
        }
        else if(arg == "crack" && query("crack") ) {
                place = "樹根裂縫";
                message_vision("$N用"+weapon->name()+"在樹根的裂縫處敲了敲。\n", me);
                addn("jingli", -10, me);
        }

        else if(arg == "cave" && query("cave") ) {
                place = "洞";
                message_vision("$N用"+weapon->name()+"在洞口地面□托、托□地輕敲著。\n", me);
                addn("jingli", -10, me);
        }
        else return notify_fail("你要搜索哪個地方？\n");

        addn_temp("search/"+place, 1, me);
        me->start_busy(1);

        if( query_temp("search/"+place, me)<3+random(3) )
                return 1;

        if(query("hide_snake") > 0) {
                check_snake(me, place);
        }
        else return notify_fail("找了這麼久，你覺得"+place+"中應該是不會藏著蛇了。\n");

        return 1;
}

void check_snake(object me, string place)
{
        object snake, here;
        int i;

        here = this_object();

        addn("hide_snake", -1, here);
        set("last_search", time(), here);

        if( place == "草叢" || place == "樹叢" ) {
                if( place == "樹叢" ) {
                        i = random(4) + 1;
                        set("searched/bush", 1);
                        }
                else {
                        i = random(4);
                        set("searched/grass", 1);
                        }
                snake = new("/d/baituo/npc/bt_snake");
                set("frightened", 1, snake);
                snake->set_kind(i);
                snake->move(here);
                message_vision(HIR"忽聽"+place+"中簌簌響動，一條"+snake->name()+"竄了出來！\n"NOR, me);
                snake->kill_ob(me);
        }
        else message_vision(place+"中傳出一陣細微的聲響，似乎有什麼東西，但是沒有出來。\n"NOR, me);

        delete_temp("search/"+place, me);

        return;
}

int do_use(string arg)
{
        object me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;

        if( arg=="fire" ) 
        write("你將火折點燃。\n");
        return 1;
}

int do_burn(string arg)
{
        object me, branch;
        string place;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙著呢。\n");

        if( !objectp(branch = present(arg, me))  && !objectp(branch = present(arg, environment(me)))  )
                return notify_fail("你要燒什麼？\n");

        if( query("id", branch) != "shuzhi" )
                return notify_fail("如果你想熏蛇，找些樹枝之類的東西來燒吧。\n");

        if( query("burning", branch) )
                return notify_fail("樹枝已經點燃了。\n");

        if( query("crack") ) {
                place = "樹根裂縫";
                if(!query("searched/crack")) message_vision("$N將樹根前的雜草撥開。\n", me);
        }
        else if( query("cave") ) place = "洞";
        else return notify_fail("在這裡燒樹枝也沒什麼用。\n");

        message_vision(HIR"$N將"+branch->name()+HIR"堆在"+place+"前，用火折點燃。\n"NOR, me);
        message_vision(WHT"一股濃煙慢慢湧入"+place+"裡........\n\n"NOR, me);
        
        set("name", "點燃的"+branch->name(), branch);
        set("long",query("long",  branch)+"現在正燃燒著，冒出濃濃的煙霧。\n", branch);
        set("burning", 1, branch);
        set("no_get", 1, branch);
        branch->move(this_object());
        remove_call_out("smoke_snake");
        call_out("smoke_snake", 7+random(3), me, branch, place); 
        me->start_busy(2);

        return 1;
}


void smoke_snake(object me, object branch, string place)
{
        object snake, here;
        int i;

        here = this_object();

        if(query("hide_snake") < 1 ) {
                message_vision("煙熏了老半天，樹枝都燒成灰了，"+place+"裡卻一點動靜也沒有。\n", me);
                destruct(branch);
                return;
        }

        addn("hide_snake", -1);
        set("last_search", time(), here);

        if( place == "樹根裂縫" ) {
                i = random(5) + 3;
                set("searched/crack", 1);
        }
        else {
                i = random(3) + 5;
                set("searched/cave", 1);
        }

        snake = new("/d/baituo/npc/bt_snake");
        set("frightened", 1, snake);
        snake->set_kind(i);
        snake->move(here);
        message_vision(HIR"忽聽一陣颼颼異聲，一條$N忍不住煙熏，從"+place+"中竄了出來！\n"NOR, snake);
        if(environment(me) == this_object())
        snake->kill_ob(me);

        delete_temp("search/"+place, me);
        destruct(branch);

        return;
}
