// zhen.c
// by Find.

#undef TEST

/*
zhen ji 建立
zhen yq 邀請
zhen in 加入
zhen huan 換陣主
zhen san 解散陣法
zhen talk 陣法説話
zhen check 陣主察看成員的狀態
*/

inherit F_CLEAN_UP;
protected void select_array(string arg,object me,string *ski);
protected void build_up(object me,string fn);

nomask int main(object me, string arg)
{
        string usr,*ski,*z_ski = ({});
        int i,n;

#ifdef TEST
        if(!wizardp(me))
                return notify_fail("測試期間只有巫師能使用陣法。\n");
#endif

        if(!stringp(arg) || arg =="")
        {
                if(!me->in_array())
                        return notify_fail("你目前沒有加入任何陣法。\n");
        // 等級 15 級
        // 救援及時、防禦等級高、陣法攻擊效果好
                else
                {
                        object *memb;
                        string out;
                        object w;
        
                        if( (w = me->query_array_master()) == me)
                                out = sprintf("你目前正在主持『%s』\n",me->query_array_name());
                        else
                                out = sprintf("你目前正在%s主持的『%s』中\n",w->name(),me->query_array_name());
        
                        memb = me->query_array_member() - ({ me,0 });
        
                        if(!sizeof(memb))
                                out += "陣形中沒有其他成員。\n";
                        else
                        {
                                out += "成員有：\n";
                                foreach(object cy in memb)
                                        out += sprintf("\t%s\n",cy->name());
                                out += sprintf("\t%s\n",me->name());
                        }

                        out += sprintf("『%s』%s。\n",
                        me->query_array_name(),
                        me->query_array_status()?
                                sprintf("正在發揮威力\n陣法等級為：%d",me->query_array_level()):
                                "的威力還沒有發揮出來");
                        write(out);
                        return 1;
                }
        }

        if(arg[0..4] == "check")
        {
                object who;

                if(!me->in_array())
                        return notify_fail("你目前沒有加入任何陣法。\n");

                if(!me->is_array_master())
                        return notify_fail("只有陣主才能查看成員的狀態。\n");

                if( !sscanf(arg,"check %s",usr)
                || !objectp(who = present(usr,environment(me)))
                || !userp(who) )
                        return notify_fail("你要查看哪個成員的狀態？\n");
                if(!me->is_array_member(who))
                        return notify_fail(sprintf("%s不是『%s』的成員。\n",
                                who->name(),me->query_array_name() ));

                write(sprintf("『%s』%s%s：\n\t當前使用武功為：%s\n\t『%s』的等級為：%d\n\t『%s』等級為：%d\n",
                        who->query_array_name(),
                        who == me?"陣主":"成員",
                        who->name(),
                        to_chinese(who->query_current_skill()),
                        who->query_array_name(),
                        who->query_skill((who->query_array_fn())->query_array_id(),1),
                        to_chinese((who->query_array_fn())->query_array_skill()),
                        who->query_skill((who->query_array_fn())->query_array_skill(),1)
                        ));

                return 1;
        }

        if(arg == "ji")        // 建立
        {
                string out;

                if(me->is_fighting())
                        return notify_fail("你正在和人打架，顧不上其它的事情。\n");

                if(me->in_team())
                        return notify_fail("你正在隊伍中，無法組織陣法。\n");

                if(me->in_array()) // xx帶領的xx
                {
                        if(me->query_array_master() == me)
                                return notify_fail(sprintf("你現在正在主持『%s』。\n",
                                me->query_array_name()));
                        else
                                return notify_fail(sprintf("你已經是%s帶領的『%s』的成員了。\n",
                                        me->query_array_master()->name(),
                                        me->query_array_name()));
                }

                if(!(ski = me->query_skills_name()) || !(n = sizeof(ski)))
                        return notify_fail("你什麼陣法都不會。\n");
                
                for(i=0;i<n;i++)
                {
                        string s;
                        if(stringp(s=SKILL_D(ski[i])) && s->is_array_skill())
                                z_ski += ({ s });
                }
                
                if(!n = sizeof(z_ski))
                        return notify_fail("你什麼陣法都不會。\n");
                if(n == 1)
                {
                        build_up(me,z_ski[0]);
                        return 1;
                }
                
                out = "你目前掌握的陣法有：\n";
                for(i=0;i<n;i++)
                        out += sprintf("\t%d. 『%s』\n",(i+1),z_ski[i]->query_name());
                out += "請選擇你要組建的陣法：(q退出)";
                write(out);
                input_to((: select_array :),me,z_ski);
                return 1;
        }

        if(arg == "san")
                return me->release_array(0);

        if(arg[0..1] == "yq")
        {
                object who;

                if(!me->in_array())
                        return notify_fail("你目前沒有加入任何陣法。\n");

                if(!me->is_array_master())
                        return notify_fail("只有陣主才能邀請別人入陣。\n");

                if(me->is_fighting())
                        return notify_fail("你正在和人打架，顧不上其它的事情。\n");

                if( !sscanf(arg,"yq %s",usr)
                || !objectp(who = present(usr,environment(me)))
                || !userp(who)
                || (who == me) )
                        return notify_fail("你要邀請誰入陣？\n");

                if(me->is_array_member(who))        // already in
                        return notify_fail(sprintf("%s已經在你主持的『%s』中了。\n",
                                who->name(),me->query_array_name()));

#ifdef TEST
                if(userp(who) && !wizardp(who))
                        return notify_fail("測試期間你只能邀請巫師入陣。\n");
#else
                if(wizardp(who))
                        return notify_fail("你不能邀請巫師入陣。\n");
#endif

                if(who->in_team())
                        return notify_fail("對方正在其它的隊伍中，無法加入你的陣法。\n");

                if(!me->can_become_member(who))
                        return 0;

                tell_object(who,sprintf("%s邀請你加入%s主持的『%s』。\n",
                        me->name(),
                        gender_pronoun(query("gender", me)),
                        me->query_array_name() ));

                tell_object(me,sprintf("你邀請%s加入你主持的。\n",
                        who->name(),me->query_array_name()));

                set_temp("pending/team", me, who);
                return 1;
        }

        if(arg == "in")
        {
                object who=query_temp("pending/team", me);

                if(!objectp(who))
                        return notify_fail("你並沒有被任何人邀請加入陣法。\n");

                if(me->in_team())
                        return notify_fail("你正在隊伍中，無法加入其它的陣法。\n");

                if(environment(who) != environment(me))
                        return notify_fail(sprintf("%s已經走了。\n",who->name()));

                if(me->in_array())
                {
                        if(me->query_array_master() == me)
                                return notify_fail(sprintf("你正在主持『%s』,無法加入其它的陣法。\n",
                                        me->query_array_name()));
                        else
                                return notify_fail(sprintf("你正在%s主持的『%s』中,無法加入其它的陣法。\n",
                                        me->query_array_master()->name(),
                                        me->query_array_name()));
                }

                if(!who->add_array_member(me))
                        return 0;

                tell_object(me,sprintf("你應邀加入%s主持的『%s』。\n",
                        who->name(),who->query_array_name() ));
                return 1;
        }

        if(arg[0..3] == "talk")
        {
                string msg;
                object *memb;

                if(!me->in_array())
                        return notify_fail("你沒有在任何陣法之中。\n");

                if(sizeof(memb = me->query_array_member()) < 2)
                        return notify_fail(sprintf("『%s』中目前還沒有其他成員。\n",
                                me->query_array_name()));

                if(!sscanf(arg,"talk %s",msg))
                        msg = "。。。\n";

                if(msg[<1] != '\n')
                        msg += "\n";

                message("tell_object",sprintf("【%s】%s(%s)：%s",
                        me->query_array_name(),
                        me->name(),
                        capitalize(query("id", me)),
                        msg ), memb);
                return 1;
        }
        write("請 help zhen 獲得此命令使用方法的幫助。\n");
        return 1;
}

protected void select_array(string arg,object me,string *ski)
{
        int n,size;

        if(!stringp(arg)
        || (arg == "")
        || !me
        || !arrayp(ski)
        || !(size = sizeof(ski)))
                return;

        if( (arg[0] == 'q')
        || (arg[0] == 'Q') )
        {
                tell_object(me,"ok.\n");
                return;
        }

        if(!sscanf("%d",n))
        {
                tell_object(me,"\n請選擇你要組建的陣法：(q退出)");
                input_to((: select_array :),me,ski);
                return;
        }

        n--;

        if( (n < 0) || (n >= size) )
        {
                tell_object(me,"\n請選擇你要組建的陣法：(q退出)");
                input_to((: select_array :),me,ski);
                return;
        }

        build_up(me,ski[n]);
        return;
}

protected void build_up(object me,string fn)
{
        if(!me
        || !stringp(fn)
        || (file_size(fn+".c") <= 0) )
                return;

        if(!fn->valid_build(me))
                return;

        if(!me->build_up_array(fn))
                return;

        message_vision(sprintf("$N開始組織『%s』。\n",me->query_array_name()),me);
}

int help(object me)
{
   write( @HELP

陣法操作命令，使用方法如下：

zhen ji
        開始組建一個你所會的陣法，如果你要是會
        多個陣法，會自動讓你選擇想要組建的陣法。
        此命令可以簡寫為： zj

zhen yq <ID>
        邀請別人加入你開始組建的陣法，<ID> 是你
        要邀請人的 ID，當然此人要符合運轉此陣法
        的基本條件。
        此命令可以簡寫為： zyq <ID>

zhen in
        如果你受到了別人的邀請，如果願意的話，可
        以用這個命令加入陣形。
        此命令可以簡寫為： zin

zhen san
        解散目前正在運用的陣法。解散命令只能由陣
        主發出。
        此命令可以簡寫為： zs

zhen talk
        已經組建的陣法成員之間可以用這個命令對話。
        此命令可以簡寫為： zt

zhen check <ID>
        陣主可以用這個命令檢查當前陣法成員的一些狀
        態，如：成員當前所使用的武功，此陣法的等級，
        陣法所要求的武功的等級。。。<ID>為要檢查成
        員的 ID。
        此命令可以簡寫為： zck <ID>

zhen
        不加任何參數的 zhen 命令可以顯示你當前所在
        陣形的一些狀態，如：陣主是誰，都有哪些成員，
        是否開始發揮威力，你們所組成的陣法的有效等
        級是多少。。。

關於陣法的詳細的幫助信息可 help zhenfa 查看。

HELP
   );
   return 1;
}
