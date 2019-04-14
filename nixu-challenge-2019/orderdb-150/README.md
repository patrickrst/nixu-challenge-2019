## ACME Order DB

**Categories:** web, misc, 2019
**Points:** 150
**Description:**

>  After successfully gaining access to the ACME intranet during a
>  red-teaming exercise we stumbled upon
>  this internal service.  See if you can make
>  it spill its secrets!
>  


## Write-up

The website in question is protected by a login page.
After trying with credentials admin/admin, we can see that a cookie `sess` is created with a Base64 encoded value that corresponds to `username=admin::logged_in=false`.
We change the value of `logged_in` to `true`, encode it and update the cookie. We are now logged in.

In the source code of the webpage, we can see a reference to LDAP (`<!-- Get documents from ldap! -->`), which hints us at a LDAP injection.
Using the following query `*))(|(a=*`, we are able to have access to secret files which one contains the flag `NIXU{c00kies_with_ldap_for_p0r1ft}`.

