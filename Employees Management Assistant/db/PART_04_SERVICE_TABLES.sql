
/****************************************************************
-- DESCRIPTION: Създаване на таблица за потребители от външни системи.
****************************************************************/

IF EXISTS (SELECT * FROM SYS.TABLES WHERE [NAME] = 'EXTERNAL_SYSTEM_TASKS')
	DROP TABLE [EXTERNAL_SYSTEM_USERS]
GO

CREATE TABLE [EXTERNAL_SYSTEM_USERS]
(  
	[ID]				INT				NOT NULL	IDENTITY(1,1),
	[DATA_VERSION]		INT				NOT NULL,
	[USERNAME]			NVARCHAR(64)	NOT NULL,
	[PASSWORD]			NVARCHAR(257)	NOT NULL,
	[PERSONAL_KEY]		NVARCHAR(129)	NOT NULL,

	CONSTRAINT [PK_EXTERNAL_SYSTEM_USERS_ID] PRIMARY KEY CLUSTERED([ID]),
)
GO

/****************************************************************
-- DESCRIPTION: Създаване на таблица за задачите, въведени от външни системи.
****************************************************************/

IF EXISTS (SELECT * FROM SYS.TABLES WHERE [NAME] = 'EXTERNAL_SYSTEM_TASKS')
	DROP TABLE [EXTERNAL_SYSTEM_TASKS]
GO

CREATE TABLE [EXTERNAL_SYSTEM_TASKS]
(  
	[ID]						INT				NOT NULL	IDENTITY(1,1),
	[DATA_VERSION]				INT				NOT NULL,
	[NAME]						NVARCHAR(64)	NOT NULL,
	[PRIORITY_ID]				INT				NOT NULL,
	[STATE_ID]					INT				NOT NULL,
	[ASSIGN_FROM_ID]			INT				NOT NULL,
	[ASSIGN_TO_ID]				INT				NOT NULL,
	[DESCRIPTION]				NVARCHAR(513)	NOT NULL,
	[EXTERNAL_PRESENTATION]		NVARCHAR(128)	NOT NULL,

	CONSTRAINT [PK_EXTERNAL_SYSTEM_TASKS_ID] PRIMARY KEY CLUSTERED([ID]),
)
GO
