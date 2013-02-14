Name:       uw-imap-toolkit
Summary:    IMAP-2007e developed by University of Washington
Version:    0.1.1
Release:    0
Group:      TO_BE/FILLED_IN
License:    TO BE FILLED IN
Source0:    %{name}-%{version}.tar.gz
BuildRequires: libgcrypt-devel
BuildRequires: pkgconfig(openssl)
BuildRequires: pkgconfig(dlog)

%description
IMAP-2007e run-time library for E-mail Framework


%package -n libuw-imap-toolkit
Summary:    IMAP-2007e developed by University of Washington
Group:      TO_BE/FILLED_IN

%description -n libuw-imap-toolkit
IMAP-2007e run-time library for E-mail Framework


%package -n libuw-imap-toolkit-devel
Summary:    IMAP-2007e developed by University of Washington
Group:      TO_BE/FILLED_IN
Requires:   libuw-imap-toolkit = %{version}-%{release}

%description -n libuw-imap-toolkit-devel
IMAP-2007e development library for E-mail Framework

%prep
%setup -q

%build
./autogen.sh
%configure --disable-static 

make %{?jobs:-j%jobs}

%install
%make_install

%post -n libuw-imap-toolkit -p /sbin/ldconfig

%postun -n libuw-imap-toolkit -p /sbin/ldconfig

%files -n libuw-imap-toolkit
%defattr(-,root,root,-) 
%{_libdir}/libuw-imap-toolkit.so.*


%files -n libuw-imap-toolkit-devel
%defattr(-,root,root,-) 
%{_libdir}/libuw-imap-toolkit.so
%{_libdir}/pkgconfig/uw-imap-toolkit.pc
%{_includedir}/uw-imap-toolkit/*