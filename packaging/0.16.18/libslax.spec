Name:        libslax
Version:     0.16.18
Release:     1%{?dist}
Summary:     The SLAX language (XSLT alternative)

Prefix:      /usr

Vender:      Juniper Networks, Inc.
Packager:    Phil Shafer <phil@juniper.net>
License:     BSD

Group:       Development/Libraries
URL:         https://github.com/Juniper/libslax
Source0:     https://github.com/Juniper/libslax/releases/0.16.18/libslax-0.16.18.tar.gz

BuildRequires:  libxml2-devel
BuildRequires:  libxslt-devel
BuildRequires:  curl-devel
BuildRequires:  libedit-devel
BuildRequires:  bison-devel
BuildRequires:  bison

%description
Welcome to libslax, an implementation of the SLAX language, an alternate
syntax for XSLT that follow the patterns of C and Perl. This library
builds on the most excellent work of Daniel Veillard et al in the
libxml2 and libxslt libraries, for which I heartily give thanks.

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
%make_install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%files
%{_bindir}/*
%{_includedir}/libslax/*
%{_libdir}/*
%{_libdir}/pkgconfig/libslax.pc
%{_libdir}/slax/extensions/*
%{_datadir}/doc/libslax/*
%docdir %{_datadir}/doc/libslax/*
%{_mandir}/*/*
%docdir %{_mandir}/*/*