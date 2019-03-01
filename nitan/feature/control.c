// /feature/control.c
// 遊戲中有數量限制的物件。
// by Find.

nomask int is_ctl_ob() { return 1; }

nomask int valid_clone()
{
        int sum,vnum;

        vnum = query("valid_number");
        if(vnum <= 0)
                vnum = 1;

        sum = sizeof(filter_array(children(base_name(this_object())), (:clonep:)));
        sum += CTLOB_D->query_save_num(base_name(this_object()));

        return (vnum >= sum);
}