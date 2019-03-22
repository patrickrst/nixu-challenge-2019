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

The website in question is protected by a login page. After trying with credentials admin/admin, we can see that a cookie `sess` is created with a Base64 encoded value.

```
dXNlcm5hbWU9YWRtaW46OmxvZ2dlZF9pbj1mYWxzZQ==
username=admin::logged_in=false
```

We change the value of `logged_in` to `true`, encode it and update the cookie. We are now logged in.

```
username=admin::logged_in=true
dXNlcm5hbWU9YWRtaW46OmxvZ2dlZF9pbj10cnVl
```

In the source code of the webpage, we can see a reference to LDAP, which hints us at a LDAP injection.

```html
<!-- Get documents from ldap! -->
```
