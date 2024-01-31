
/****************************************************************
-- DESCRIPTION: Създаване на база данни.
****************************************************************/

IF EXISTS (SELECT [NAME] FROM SYS.DATABASES WHERE [NAME] = N'EMPLOYEES_MANAGEMENT_ASSISTANT')
	DROP DATABASE [EMPLOYEES_MANAGEMENT_ASSISTANT];

CREATE DATABASE [EMPLOYEES_MANAGEMENT_ASSISTANT]
ON PRIMARY
	(NAME = management_assistant_dat,
	FILENAME = N'\employees_management_assistant.mdf',  
	SIZE = 8MB,  
	MAXSIZE = UNLIMITED,  
	FILEGROWTH = 64MB)  
LOG ON
	(NAME = management_assistant_log,  
	FILENAME = N'\employees_management_assistant_log.ldf',  
	SIZE = 8MB,  
	MAXSIZE = UNLIMITED,
	FILEGROWTH = 64MB)
GO
