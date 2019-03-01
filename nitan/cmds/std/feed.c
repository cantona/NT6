// Filename : /cmds/std/feed.c
// Last Modified by winder on Aug. 5 2001

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, pet;
        string owner, food, ob;
        int i, j, lvl, effect;

        seteuid(getuid());

        if(!arg || sscanf(arg, "%s to %s", food, ob) !=2)
                return notify_fail("你要喂什麼東西給誰？\n");
        if(!objectp(obj = present(food, me)) ) 
                return notify_fail("你身上沒有這樣東西啊。\n");
        if(!objectp(pet = present(ob, environment(me))) || !living(pet))
                return notify_fail("這裡沒有這樣的動物。\n");
        if( query("race", pet) == "人類" )
                return notify_fail(pet->name()+"是寵物麼？瞪大眼睛看看！\n");
        if(pet->is_busy() )
                return notify_fail(pet->name()+"正忙著呢，哪吃得下什麼！\n");
        if(pet->is_busy() )
                return notify_fail(pet->name()+"正忙著呢，哪吃得下什麼！\n");
        if(me->is_busy() )
                return notify_fail("你正忙著呢，什麼也做不了！\n");
        if(pet->is_fighting() )
                return notify_fail("它正在打架呢，你難道沒看見？！\n");
        if(me->is_fighting() )
                return notify_fail("一邊打架一邊喂食？你真是活膩了！\n");
        if( !wizardp(me) && query_temp("feeded", pet) )
                return notify_fail("人一次不能多吃東西，吃多了會拉肚子，"+query("name", pet)+"也一樣。\n");
        if( query("id", me) != query_temp("owner", pet) )
                return notify_fail("你看到"+query("name", pet)+"上前聞了兩下，結果一腳踢開了。\n");
        if( !query("siliao_supply", obj) )
                return notify_fail("似乎"+query("name", pet)+"對這樣東西興趣不大。\n");
        if( !query("siliao_remaining", obj) )
                return notify_fail( obj->name() + "已經沒什麼好吃的了。\n");
        if( query("food", pet) >= pet->max_food_capacity() )
                return notify_fail(pet->name()+"已經吃太飽了，再也塞不下任何東西了。\n");
        set("value", 0, obj);
        addn("siliao_remaining", -1, obj);
        me->start_busy(1);
// 寵物食物狀態改變。
        addn("food",query("siliao_supply",  obj), pet);
// 延時進食，不能連續吃。剛吃完也不能讓寵物退出。連續機器人喂76天達到100級。
// 9天可以達到50級。
        set_temp("feeded", "1", pet);
        call_out("del", 20, pet);
// 寵物升級，與馴獸無關。
        if( query("owner", pet) == query("id", me) )
        {
// 食物作用改變，累計以便升級。
                if( query("siliao_effect", obj) )
                        addn("feed",query("siliao_effect",  obj), pet);
// 喂養長經驗。
                addn("combat_exp", 5+random(10), pet);
                i=query("feed", pet);
                j=query("level", pet);
                if(i>=2+j*j)
                {
                        tell_object(me,HIY"你喂了這一次食物後，發覺"+query("name", pet)+"似乎顯得更強健、也更聽話了！\n"NOR);
// 喂養長級別。
                        addn("level", 1, pet);
                        set("feed", 0, pet);
// 喂養長馴服度。
                        addn("obe", 1, pet);
                        lvl=query("level", pet);
                }
                addn("max_qi", lvl, pet);
                addn("max_jing", lvl, pet);
        }
        if( !query("siliao_remaining", obj) )
        {
                delete_temp("apply/long", obj);
                if( query("finish_msg", obj) )
                        message_vision(query("finish_msg", obj),pet,obj);
                else
                {
                        message_vision("$N拿出一"+query("unit", obj)+query("name", obj)+"來，向$n招了招手。\n$n很馴順的走了過去，一把叼起了"+query("name", obj)+"，吃了個幹幹凈凈。\n",me,pet);
                }
                if( !obj->finish_eat() ) destruct(obj);
        } 
        else
        {
                if( query("eat_msg", obj) )
                        message_vision(query("eat_msg", obj),pet,obj);
                else 
                        message_vision("$N拿出一"+query("unit", obj)+query("name", obj)+"來，向$n招了招手。\n$n很馴順的走了過去，一把叼起了"+query("name", obj)+"，狠狠就是一口。\n",me,pet);
        }
        if( !obj ) return 1;
        
        return 1;
}

void del(object pet)
{
        delete_temp("feeded", pet);
}

int help(object me)
{
        write(@HELP
指令格式 : feed <飼料> to <動物名>

    此指令可用于喂養你所馴服的動物。

    對于已經馴服的動物，可以進行下述指令：

基本指令：
        come <動物名>:                  讓動物跟隨主人行動。
        stay:                           停止動物的跟隨狀態。
        attack <某物>:                  讓動物攻擊敵人。
        stop <動物名>:                  讓動物停止對人的攻擊。
        release:                        結束主奴狀態，將動物放離。

特殊指令：（只對某些動物適用）
        ride <動物名>:                  騎，如騎馬，虎，雕，鯊等。
        unride <動物名>:                下，離開坐騎。
        feed <飼料> to <動物名>:        替動物喂食。
        imbibe <動物名>:                給動物飲水。

HELP
        );
        return 1;
}
