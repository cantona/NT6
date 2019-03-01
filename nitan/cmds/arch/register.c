// register.c
// Created by Xiang@XKX
// Updated by doing

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

protected int register_user(string wizid, string name, string email)
{
        object ob, body;

              if (objectp(body = find_player(name)))
        {
                set("registered", 1, body);
                set("email", email, body);
                body->save();
                return 1;
        }

        ob = new(LOGIN_OB);
        set("id", name, ob);
        body = LOGIN_D->make_body(ob);
        destruct(ob);
        if (! body)
                destruct(ob);
        else
        if (! body->restore())
        {
                destruct(body);
        } else
        {
                set("registered", 1, body);
                set("email", email, body);
                body->save();
                destruct(body);
                return 1;
        }

        return 0;
}

int main(object me, string arg)
{
        string id, email;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s", id, email) != 2)
                return notify_fail("指令格式：register <id> <email>\n");

        if (wiz_level(me) < wiz_level(id))
                return notify_fail("你沒有權限為此人注冊。\n");

        switch(register_user(query("id", me),id,email) )
        {
        case 0:  return notify_fail("登記失敗。\n"); break;
        default: return notify_fail("用戶(" + id + ")已經成功地被您登記了。\n"); break;
        }
}

int help(object me)
{
        write(@HELP
指令格式：register <id> <email>

這個指令可以給還沒有登記過的用戶進行登記，或者給已經登記的用
戶設定新的登記郵箱。
HELP );
        return 1;
}