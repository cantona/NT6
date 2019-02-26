#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name("龍元", ({ "dragon soul" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是龍的內丹，雞蛋大小，如火焰般赤紅。用法：boost\n");
                set("unit", "顆");
                set("value", 50000);
                set("no_drop",1);
        }
        setup();
}

void init()
{
  if(this_player()==environment())
  add_action("boost_skill","boost");
}

int boost_skill()
{
        int force_limit, neili_limit, force_skill, add_skill, improve;

        object ob, *list, couple_ob;
        string theskill;
        int thelevel = 0;
        mapping skl, lrn, map;
        string *sname, *mapped,target,cardname;
        int i, marry_flag;
        ob = this_player();
        skl = ob->query_skills(); 

        force_limit = ob->query_skill("force")*10;
        neili_limit=query("max_neili", ob);
        force_skill = ob->query_skill("force", 1); 

        if( ob->query_condition("putizi_drug")>0 || query("dragon_soul", ob)>100 )
        {
                addn("max_neili", -50, ob);
                message_vision(HIR "$N試圖吸納龍元，但身體承受不了，結果適得其反！\n" NOR, ob);
                destruct(this_object());
                return 1;
        }
        else if ( neili_limit <= force_limit  )
        {
                addn("max_neili", 50, ob);
                addn("neili", 50, ob);

                message_vision(HIY "$N運勁吸納龍元，只見$N面色赤紅如火，體內真氣源源而生。\n" NOR, this_player());
                ob->apply_condition("putizi_drug", 1000);
        }        if(!sizeof(skl)) {
                write( "你目前並沒有學會任何技能。\n");
                return 1;
        }
        sname  = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        lrn = ob->query_learned();
        if( !mapp(lrn) ) lrn = ([]);

       for(i=0; i<sizeof(skl); i++) {
                if(skl[sname[i]] > thelevel) {theskill = sname[i]; thelevel = skl[sname[i]];} 
        }
        ob->set_skill(theskill, (int)thelevel+1);
        addn("dragon_soul", 1, ob);
message_vision("$N的"+to_chinese(theskill)+"增強了。\n", this_player());
destruct(this_object());
return 1;
}
