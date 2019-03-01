// vote jail
#include <command.h> 
#include <vote.h> 
#include <ansi.h>
#define JAIL "/d/beijing/jail"

inherit F_CONDITION;

int clear_vote(object me);

int vote(object me, object victim)
{
  int reason; // vote for what?
  int vv;        // valid voter numbers
  int vc;         // vote count;
  int df;
  int i;
  string *juror, *ips , my_ip;
  object *inv;

  if (me == victim)
  {
        if (random(2)) addn("vote/abuse", 10, me);
          return notify_fail("你不是開玩笑吧？當心被剝奪表決權！\n");
  }

  if( (reason=query("vote/reason", victim))>0 && (reason != V_CHBLK) )
  {
          return notify_fail("要把當前的表決完成以後才可以提新的動議。\n");
  }

  if( base_name(environment(victim)) == JAIL) 
  {
          return notify_fail(victim->name()+"已經被關在刑部大牢裡了。\n");
  }

  if (reason <= 0)
  {
          set("vote/reason", V_CHBLK, victim);
  }
  
  my_ip = query_ip_name(me);

  // dont allow me to vote twice for the same issue
  juror=query("vote/juror", victim);
  
  if( !pointerp(juror) )
  {
         juror = set("vote/juror", ({ my_ip }), victim );
  } else if( member_array(my_ip, juror) == -1 || wizardp(me))
  {
        juror += ({ my_ip });
         set("vote/juror", juror, victim );
  } else
  {
        addn("vote/abuse", 10, me);
          return notify_fail("一人一票！濫用表決權是要受懲罰的！\n");
  }
  ips = ("/cmds/std/vote")->valid_voters(me);
  vv = sizeof(ips);
  for (i=0;i<sizeof(juror);i++)
  {
          if (member_array(juror[i],ips)==-1)
           addn("vote/count", -1, vc=victim);
  }
  addn("vote/count", 1, vc=victim);

//  df = (int)((vv - vc)/2);
  df = vv - vv/2 - vc;
  if (vv < 8) df = 4 - vc;

  if (df>0)
  {
        shout( HIG "【表決】"+me->name()+"投票將" +victim->name()
                        +"送往刑部大牢，還差"+sprintf("%d", df)+"票。\n" NOR);
        write( HIG "【表決】"+me->name()+"投票將" +victim->name()
                        +"送往刑部大牢，還差"+sprintf("%d", df)+"票。\n" NOR);
        victim->apply_condition("vote_clear", 10);
  } else 
  {
        shout( HIG "【表決】"+me->name()+"投票將" +victim->name()
                        +"送往刑部大牢。"+victim->name()+"已經被送往刑部大牢了！\n" NOR);
        write( HIG "【表決】"+me->name()+"投票將" +victim->name()
                        +"送往刑部大牢。"+victim->name()+"已經被送往刑部大牢了！\n" NOR);
                        
        victim->apply_condition("vote_clear", -10);
        delete("vote/juror", victim);
        if( !wizardp(victim) ) {
                inv = all_inventory(victim);
                for(i=0; i<sizeof(inv); i++)
                        if( !inv[i]->query_autoload() )
                                DROP_CMD->do_drop(victim, inv[i]);
        }
//        victim->set("xkx_jail", 1);
        victim->move(JAIL);
  } 
  
  return 1;
}
